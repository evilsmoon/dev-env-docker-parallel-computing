FROM debian:stable

RUN apt-get update -y \
      && apt-get upgrade -y  \
      && apt-get install wget gcc g++ gfortran libdcmtk-dev git valgrind perl make build-essential libibnetdisc-dev -y

RUN mkdir /opt/openmpi

RUN cd /opt/openmpi

WORKDIR /opt/openmpi

ARG OPENMPI_VERSION="4.1.4"
ARG OPENMPI_MAJOR_VERSION="v4.1"

RUN wget https://download.open-mpi.org/release/open-mpi/${OPENMPI_MAJOR_VERSION}/openmpi-${OPENMPI_VERSION}.tar.bz2 \
      && tar -jxf openmpi-${OPENMPI_VERSION}.tar.bz2

RUN cd openmpi-${OPENMPI_VERSION} \
      && ./configure --prefix="/opt/openmpi" \
      && make all  && make install

ENV PATH="$PATH:/opt/openmpi/bin"

ENV LD_LIBRARY_PATH="LD_LIBRARY_PATH:/opt/openmpi/lib/"

RUN cd 

RUN mkdir /opt/cmake

RUN cd /opt/cmake

WORKDIR /opt/cmake

ARG CMAKE_VERSION="v3.25.0-rc3"

ARG CMAKE_LINUX_VERSION="3.25.0-rc3-linux-x86_64"

RUN wget https://github.com/Kitware/CMake/releases/download/${CMAKE_VERSION}/cmake-${CMAKE_LINUX_VERSION}.tar.gz \
      && tar xvf cmake-${CMAKE_LINUX_VERSION}.tar.gz

RUN cd cmake-${CMAKE_LINUX_VERSION}

ENV PATH="$PATH:/opt/cmake/cmake-${CMAKE_LINUX_VERSION}/bin"


RUN cd

RUN cd /home

WORKDIR /home

RUN git clone https://github.com/ramirew/dip.git

RUN cd dip

WORKDIR /home/dip

RUN sh build.sh

RUN cd

RUN mkdir /home/second-order

RUN cd /home/second-order

WORKDIR /home/second-order

COPY ./ ./
