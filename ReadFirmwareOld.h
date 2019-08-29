/*
 * ReadFirmwareOld.h
 *
 *  Created on: 29 авг. 2019 г.
 *      Author: BlaBu
 */

#ifndef READFIRMWAREOLD_H_
#define READFIRMWAREOLD_H_

#include "IIReader.hpp"
#include <fstream>
#include "BufferInterface.hpp"

class firmwareDiscriptorOld : public IFirmwareReader {
	private:
	const std::vector<byteVector_ptr> FileBuffer;
	firmwareDiscriptorOld()=delete;
	firmwareDiscriptorOld& operator=(firmwareDiscriptorOld&)=delete;
	public:
	firmwareDiscriptorOld(const std::vector<byteVector_ptr>&& origin): IFirmwareReader(origin.size()), FileBuffer(std::move(origin)) {}
	virtual const byteVector_t* const nextSector(const std::uint32_t sectorNumb) const;
};


class ReadFirmwareOLd : public IReader {
	std::ifstream file;
	ReadFirmwareOLd() {}
public:
	static std::shared_ptr< IReader> const GetFirmwareReader() {
		return std::shared_ptr<ReadFirmwareOLd>(new ReadFirmwareOLd());
	}
	const firmware_ptr readFirmwareFile(const std::string& fileAddr);
	virtual ~ReadFirmwareOLd() = default;
};

#endif /* READFIRMWAREOLD_H_ */
