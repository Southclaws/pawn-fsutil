# -
# Setup test requirements
# -

test-setup:
	sampctl package build --forceEnsure
	cd test && sampctl server ensure

# -
# Run Tests
# -

test-windows:
	sampctl package build
	cd test && sampctl server run

test-linux:
	sampctl package build
	cd test && sampctl server run --container

# -
# Build (Linux)
# -

build-linux:
	rm -rf build
	docker build -t southclaws/fsutil-build .
	docker run \
		-v $(shell pwd):/root/fsutil \
		--entrypoint make \
		--workdir /root/fsutil \
		southclaws/fsutil-build \
		build-inside

build-interactive:
	docker run \
		-v $(shell pwd):/root/fsutil \
		-it \
		southclaws/fsutil-build

build-inside:
	mkdir build-linux && cd build-linux && cmake .. && make
