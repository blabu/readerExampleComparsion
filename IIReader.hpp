/*
 * IReader.hpp
 *
 *  Created on: 29 авг. 2019 г.
 *      Author: BlaBu
 */

#ifndef IIREADER_HPP_
#define IIREADER_HPP_

#include <vector>
#include <memory>

typedef  std::vector<std::uint8_t> byteVector_t;
typedef std::vector<std::shared_ptr<byteVector_t> > bufferList_t;
typedef std::shared_ptr<bufferList_t> bufferPtr_t;

class IFirmwareReader {
private:
	const std::uint32_t size;
	IFirmwareReader()=delete;
public:
	IFirmwareReader(std::uint32_t s) : size(s){}
	virtual ~IFirmwareReader()=default;
	virtual std::uint32_t getSize()const { return size; }
	virtual const byteVector_t*const nextSector(const std::uint32_t sectorNumb) const = 0;
};

typedef std::shared_ptr<IFirmwareReader> firmware_ptr;

class IReader {
public:
	virtual ~IReader()=default;
	virtual const firmware_ptr readFirmwareFile(const std::string& fileAddr) = 0;
};


#endif /* IIREADER_HPP_ */
