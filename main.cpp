/*
 * main.cpp
 *
 *  Created on: 28 авг. 2019 г.
 *      Author: BlaBu
 */

#include <thread>
#include "ReadFirmware.h"
#include "ReadFirmwareOld.h"
#include "ReadFirmwareOrigin.h"
#include <iostream>
#include <string>

void check(std::uint16_t numb, const std::string& file, IReader* r) {
	for(std::uint16_t i = numb+1; i!=0; i--) {
		auto re(r->readFirmwareFile(file));
	}
}

void checkOLD(std::uint16_t numb, const std::string& file, std::shared_ptr<IReader> r) {
	for(std::uint16_t i = numb+1; i!=0; i--) {
		auto re(r->readFirmwareFile(file));
	}
}

int main(int arg_c, char* arg_v[]) {
	if(arg_c != 4) {
		std::cerr<<"Error not find file name\n";
		std::cerr<<"Usage: You must specified reader (1 or 2 or 3), number of times read file and it name\n";
		std::cerr<<"Example "<< std::string(arg_v[0]) <<" 1 10 test.text\n";
		std::cerr<<"Example "<< std::string(arg_v[0]) <<" 2 10000 test.text\n";
		return 1;
	}
	std::list<std::thread*> threadGroup;
	auto numb = atoi(arg_v[2]);
	if(std::string(arg_v[1]).find('1') != std::string::npos) {
		std::cout<<"Check with pointer reader\n";
		for(int i = 0; i<50; i++) {
			std::thread* th = new std::thread(std::bind(check, static_cast<std::uint16_t>(numb),std::string(arg_v[3]),ReadFirmware::GetFirmwareReader()));
			threadGroup.push_back(th);
		}
		auto r = ReadFirmware::GetFirmwareReader()->readFirmwareFile(std::string(arg_v[3]));
		for(std::uint32_t i = 0; i<r->getSize(); i++) {
			std::cout<<std::string(r->nextSector(i)->cbegin(), r->nextSector(i)->cend())<<std::endl;
		}
	} else if(std::string(arg_v[1]).find('2') != std::string::npos) {
		std::cout<<"Check with origin reader\n";
		for(int i = 0; i<50; i++) {
			std::thread* th = new std::thread(std::bind(check, static_cast<std::uint16_t>(numb),std::string(arg_v[3]),ReadFirmwareOrigin::GetFirmwareReader()));
			threadGroup.push_back(th);
		}
		auto r = ReadFirmwareOrigin::GetFirmwareReader()->readFirmwareFile(std::string(arg_v[3]));
		for(std::uint32_t i = 0; i<r->getSize(); i++) {
			std::cout<<std::string(r->nextSector(i)->cbegin(), r->nextSector(i)->cend())<<std::endl;
		}
	} else {
		std::cout<<"Check with old reader\n";
		for(int i = 0; i<50; i++) {
			std::thread* th = new std::thread(std::bind(checkOLD, static_cast<std::uint16_t>(numb), std::string(arg_v[3]), ReadFirmwareOLd::GetFirmwareReader()));
			threadGroup.push_back(th);
		}
		auto r = ReadFirmwareOLd::GetFirmwareReader()->readFirmwareFile(std::string(arg_v[3]));
		for(std::uint32_t i = 0; i<r->getSize(); i++) {
			std::cout<<std::string(r->nextSector(i)->cbegin(), r->nextSector(i)->cend())<<std::endl;
		}
	}
	for(auto th: threadGroup) {
		th->join();
		delete th;
	}
	return 0;
}

