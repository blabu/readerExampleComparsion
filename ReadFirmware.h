/*
 * ReadFirmware.h
 *
 *  Created on: 28 авг. 2019 г.
 *      Author: BlaBu
 */

#ifndef READFIRMWARE_H_
#define READFIRMWARE_H_

#include <mingw.thread.h>
#include <mingw.mutex.h>
#include <list>
#include <map>
#include "IIReader.hpp"

class firmwareDiscriptor : public IFirmwareReader {
	private:
	const bufferPtr_t FileBuffer;
	firmwareDiscriptor()=delete;
	firmwareDiscriptor& operator=(firmwareDiscriptor&)=delete;
	public:
	firmwareDiscriptor(const firmwareDiscriptor& origin): IFirmwareReader(origin.getSize()), FileBuffer(origin.FileBuffer){}
	firmwareDiscriptor(const bufferPtr_t& data): IFirmwareReader(data->size()), FileBuffer(data) {}
	virtual ~firmwareDiscriptor()=default;
	virtual const byteVector_t*const nextSector(const std::uint32_t sectorNumb) const;
};

class ReadFirmware : public IReader {
	std::mutex fileLock;
	std::mutex mapLock;
	std::map<std::string, bufferPtr_t> allFirmware; // Мапа всех считанных прошивок с ключом по имени
	ReadFirmware() {}
public:
	static IReader*const GetFirmwareReader() {
		static ReadFirmware reader;
		return &reader;
	}
	const firmware_ptr readFirmwareFile(const std::string& fileAddr);
	virtual ~ReadFirmware() = default;
};


#endif /* READFIRMWARE_H_ */
