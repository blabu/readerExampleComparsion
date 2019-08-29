/*
 * ReadFirmware.cpp
 *
 *  Created on: 28 авг. 2019 г.
 *      Author: BlaBu
 */

#include "ReadFirmware.h"
#include <fstream>
#include <iostream>

const std::vector<std::uint8_t>*const firmwareDiscriptor::nextSector(const std::uint32_t sectorNumb) const {
	if(FileBuffer != nullptr && FileBuffer.get() != nullptr) {
		auto res(FileBuffer->at(sectorNumb));
		if(res != nullptr && res.get() != nullptr) return res.get();
	}
	throw std::out_of_range("Next sector not exists" + std::to_string(sectorNumb));
}

const firmware_ptr ReadFirmware::readFirmwareFile(const std::string& fileAddr) {
	std::lock_guard<std::mutex> mapLk(mapLock);
	bufferPtr_t buff(new bufferList_t);
	try {
		buff = allFirmware.at(fileAddr);
	} catch(const std::out_of_range&) { // Не нашли онлайн
		std::lock_guard<std::mutex> fileLk(fileLock);
		std::pair<std::string, bufferPtr_t> descriptor(fileAddr,buff);
		buff->clear();
		try {
			std::ifstream file(fileAddr, std::ios_base::in | std::ios_base::binary);
			if (file.is_open()) {
				descriptor.second->clear();
				do {
					auto segment = std::shared_ptr< byteVector_t >(new byteVector_t(512));
					segment->resize(512); // TODO try delete
					file.read(reinterpret_cast<char*>(segment->data()), 512);
					descriptor.second->push_back(std::move(segment));
				}while(!file.eof());
				file.close();
				auto res = std::shared_ptr<IFirmwareReader>(new firmwareDiscriptor(descriptor.second));
				allFirmware.insert(std::move(descriptor));
				return res;
			}
		} catch(const std::ifstream::failure& e) {
			std::cout<<"Can not open file. File does not exist\n";
			throw e;
		}
	}
	return std::shared_ptr<IFirmwareReader>(new firmwareDiscriptor(buff));
}
