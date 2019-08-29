/*
 * ReadFirmwareOld.cpp
 *
 *  Created on: 29 авг. 2019 г.
 *      Author: BlaBu
 */

#include "ReadFirmwareOld.h"
#include <iostream>
#include <mingw.thread.h>
#include <mingw.mutex.h>

const byteVector_t*const firmwareDiscriptorOld::nextSector(const std::uint32_t sectorNumb) const {
    try {
        byteVector_ptr res(FileBuffer.at(sectorNumb));
        return static_cast<byteVector_t*>(res.get());
    }
    catch (std::out_of_range& e) {
        throw e;
    }
}

const firmware_ptr ReadFirmwareOLd::readFirmwareFile(const std::string& fileAddr) {
	static std::mutex fileMtx;
	std::vector<byteVector_ptr> FileBuffer;
	try {
		std::lock_guard<std::mutex> lk(fileMtx);
		file.open(fileAddr, std::ios_base::in | std::ios_base::binary);
	}
	catch (const std::ifstream::failure& e) {
		std::cerr<< "Exception when try open file ", e.what();
		if (file.is_open()) file.close();
		return std::shared_ptr<IFirmwareReader>(new firmwareDiscriptorOld(std::move(FileBuffer)));
	}
	try {
		if (!file.is_open()) {
			std::cerr<< "File " << fileAddr << " can not be open\n";
			return std::shared_ptr<IFirmwareReader>(new firmwareDiscriptorOld(std::move(FileBuffer)));
		}
		do {
			byteVector_ptr tempBuf(new byteVector(512));
			tempBuf->resize(512);
			file.read((char*)(tempBuf->data()), 512);
			FileBuffer.push_back(tempBuf);
		} while (!file.eof());
	}
	catch (const std::ifstream::failure& e) {
		std::cerr<<"Exception when try read file for load firmaware "<< e.what();
		FileBuffer.clear();
	}
	if(file.is_open()) file.close();
    return std::shared_ptr<IFirmwareReader>(new firmwareDiscriptorOld(std::move(FileBuffer)));
}
