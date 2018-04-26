FROM maddinat0r/debian-samp

# -
# zlib
# -

RUN wget http://prdownloads.sourceforge.net/libpng/zlib-1.2.11.tar.gz && \
    tar -xzf zlib-1.2.11.tar.gz && \
    cd zlib-1.2.11 && \
    CFLAGS=-m32 ./configure --static && \
    make && make install && \
    cd ..

# -
# Boost
# -

RUN wget https://dl.bintray.com/boostorg/release/1.67.0/source/boost_1_67_0.tar.gz && \
    tar -xzf boost_1_67_0.tar.gz
RUN cd boost_1_67_0 && \
    ./bootstrap.sh && \
    ./b2 link=static address-model=32 -sZLIB_SOURCE=/root/zlib-1.2.11 && \
    cd ..
ENV BOOST_ROOT=/root/boost_1_67_0

# -
# Build restful plugin by mounting repo directory into container and executing
# `make build-inside` as the entrypoint.
# -
