#!/usr/bin/python
import lutin.debug as debug
import lutin.tools as tools


def get_type():
	return "LIBRARY"

def get_desc():
	return "E-chrono: Ewol chrono"

def get_licence():
	return "MPL-2"

def get_compagny_type():
	return "com"

def get_compagny_name():
	return "atria-soft"

def get_maintainer():
	return "authors.txt"

def get_version():
	return "version.txt"

def configure(target, my_module):
	# add extra compilation flags:
	my_module.add_extra_flags()
	# add the file to compile:
	my_module.add_src_file([
	    'echrono/echrono.cpp',
	    'echrono/debug.cpp',
	    'echrono/Duration.cpp',
	    'echrono/Time.cpp',
	    'echrono/Steady.cpp',
	    'echrono/Clock.cpp',
	    ])
	my_module.add_header_file([
	    'echrono/echrono.hpp',
	    'echrono/Duration.hpp',
	    'echrono/Time.hpp',
	    'echrono/Steady.hpp',
	    'echrono/Clock.hpp',
	    ])
	
	# name of the dependency
	my_module.add_depend([
	    'elog',
	    'etk-base',
	    ])
	
	my_module.add_path(".")
	
	return True

