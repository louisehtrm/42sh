ninja:
	ninja -C builddir
	cp builddir/42sh .

check: tests/test.sh
	sh tests/test.sh
clean:
	rm -f 42sh
