/*
 * ReadFirmwareOrigin2.h
 *
 *  Created on: 29 авг. 2019 г.
 *      Author: BlaBu
 */

#ifndef READFIRMWAREORIGIN_H_
#define READFIRMWAREORIGIN_H_

#include "IIReader.hpp"
#include <mingw.thread.h>
#include <mingw.mutex.h>
#include <list>
#include <map>

class firmwareDiscriptorOrigin : public IFirmwareReader {
	private:
	const bufferList_t FileBuffer;
	firmwareDiscriptorOrigin()=delete;
	firmwareDiscriptorOrigin& operator=(firmwareDiscriptorOrigin&)=delete;
	public:
	firmwareDiscriptorOrigin(const firmwareDiscriptorOrigin& origin): IFirmwareReader(origin.getSize()), FileBuffer(origin.FileBuffer){}
	firmwareDiscriptorOrigin(const bufferList_t& data): IFirmwareReader(data.size()), FileBuffer(data){}
	virtual const byteVector_t*const nextSector(const std::uint32_t sectorNumb) const;
};

class ReadFirmwareOrigin : public IReader {
	std::mutex fileLock;
	std::mutex mapLock;
	std::map<std::string, bufferList_t> allFirmware; // Мапа всех считанных прошивок с ключом по имени
	ReadFirmwareOrigin() {}
public:
	static  IReader*const GetFirmwareReader() {
		static ReadFirmwareOrigin reader;
		return &reader;
	}
	const firmware_ptr readFirmwareFile(const std::string& fileAddr);
	virtual ~ReadFirmwareOrigin() = default;
};


#endif /* READFIRMWAREORIGIN_H_ */
