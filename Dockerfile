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
# Build restful plugin by mounting repo directory into container and executing
# `make build-inside` as the entrypoint.
# -
