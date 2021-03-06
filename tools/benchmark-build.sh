#!/bin/sh

# Run this script at the directory which holds it.

set -x
  
SOURCE_DIR=`pwd`/..
BUILD_TYPE=release
BUILD_DIR=${SOURCE_DIR}/build-${BUILD_TYPE}

mkdir -p $BUILD_DIR \
  && cd $BUILD_DIR \
  && cmake -DCMAKE_BUILD_TYPE=$BUILD_TYPE $SOURCE_DIR \
  && make -j4\
  && cp -rf $BUILD_DIR/bin/example_pingpong* ../benchmark/tcp/evpp \
  && cp -rf $BUILD_DIR/bin/benchmark_tcp_asio_* ../benchmark/tcp/asio \
  && cp -rf $BUILD_DIR/bin/benchmark_tcp_libevent_* ../benchmark/tcp/libevent \

