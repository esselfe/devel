
default:
	make -C src
	@ls -li --color=auto devel

clean:
	make -C src clean
