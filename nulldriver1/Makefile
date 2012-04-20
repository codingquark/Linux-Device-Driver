#Makefile - makefile for Nulldriver

ifneq ($(KERNELRELEASE),)
	obj-m := nulldriver1.o

else
	KERNEL_SOURCE := /lib/modules/2.6.32-220.7.1.*/build/
	PWD := $(shell pwd)

default:
	${MAKE} -C $(KERNEL_SOURCE) SUBDIRS=${PWD} modules
clean:
	${MAKE} -C $(KERNEL_SOURCE) SUBDIRS=${PWD} clean
endif
