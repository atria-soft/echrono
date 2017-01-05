e-chrono
========

`e-chrono` Virualize the std::chono interface to permit to have a slow virtual clock

Release (master)
----------------

[![Build Status](https://travis-ci.org/atria-soft/echrono.svg?branch=master)](https://travis-ci.org/atria-soft/echrono)
[![Coverage Status](http://atria-soft.com/ci/coverage/atria-soft/echrono.svg?branch=master)](http://atria-soft.com/ci/atria-soft/echrono)
[![Test Status](http://atria-soft.com/ci/test/atria-soft/echrono.svg?branch=master)](http://atria-soft.com/ci/atria-soft/echrono)
[![Warning Status](http://atria-soft.com/ci/warning/atria-soft/echrono.svg?branch=master)](http://atria-soft.com/ci/atria-soft/echrono)

[![Build Status](http://atria-soft.com/ci/build/atria-soft/echrono.svg?branch=master&tag=Linux)](http://atria-soft.com/ci/atria-soft/echrono)
[![Build Status](http://atria-soft.com/ci/build/atria-soft/echrono.svg?branch=master&tag=MacOs)](http://atria-soft.com/ci/atria-soft/echrono)
[![Build Status](http://atria-soft.com/ci/build/atria-soft/echrono.svg?branch=master&tag=Mingw)](http://atria-soft.com/ci/atria-soft/echrono)

[![Build Status](http://atria-soft.com/ci/build/atria-soft/echrono.svg?branch=master&tag=Android)](http://atria-soft.com/ci/atria-soft/echrono)
[![Build Status](http://atria-soft.com/ci/build/atria-soft/echrono.svg?branch=master&tag=IOs)](http://atria-soft.com/ci/atria-soft/echrono)

Developement (dev)
------------------

[![Build Status](https://travis-ci.org/atria-soft/echrono.svg?branch=dev)](https://travis-ci.org/atria-soft/echrono)
[![Coverage Status](http://atria-soft.com/ci/coverage/atria-soft/echrono.svg?branch=dev)](http://atria-soft.com/ci/atria-soft/echrono)
[![Test Status](http://atria-soft.com/ci/test/atria-soft/echrono.svg?branch=dev)](http://atria-soft.com/ci/atria-soft/echrono)
[![Warning Status](http://atria-soft.com/ci/warning/atria-soft/echrono.svg?branch=dev)](http://atria-soft.com/ci/atria-soft/echrono)

[![Build Status](http://atria-soft.com/ci/build/atria-soft/echrono.svg?branch=dev&tag=Linux)](http://atria-soft.com/ci/atria-soft/echrono)
[![Build Status](http://atria-soft.com/ci/build/atria-soft/echrono.svg?branch=dev&tag=MacOs)](http://atria-soft.com/ci/atria-soft/echrono)
[![Build Status](http://atria-soft.com/ci/build/atria-soft/echrono.svg?branch=dev&tag=Mingw)](http://atria-soft.com/ci/atria-soft/echrono)

[![Build Status](http://atria-soft.com/ci/build/atria-soft/echrono.svg?branch=dev&tag=Android)](http://atria-soft.com/ci/atria-soft/echrono)
[![Build Status](http://atria-soft.com/ci/build/atria-soft/echrono.svg?branch=dev&tag=IOs)](http://atria-soft.com/ci/atria-soft/echrono)


Instructions
============

download Build system:
----------------------

	sudo pip install lutin
	sudo pip install pillow

download the software:
----------------------

	mkdir WORKING_DIRECTORY
	cd WORKING_DIRECTORY
	git clone https://github.com/atria-soft/elog.git
	git clone https://github.com/atria-soft/etk.git
	git clone https://github.com/atria-soft/echrono.git
	git clone https://github.com/generic-library/gtest-lutin.git --recursive

Compile software:
-----------------

	cd WORKING_DIRECTORY
	lutin -C -P echrono


License (MPL v2.0)
=====================
Copyright echrono Edouard DUPIN

Licensed under the Mozilla Public License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

    https://www.mozilla.org/MPL/2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.

