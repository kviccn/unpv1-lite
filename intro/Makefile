include ../Make.defines.in

daytimetcpcli: daytimetcpcli.c
	$(CC) -o $@ $< $(CFLAGS)

daytimetcpsrv: daytimetcpsrv.c
	$(CC) -o $@ $< $(CFLAGS)

daytimetcpsrv1: daytimetcpsrv1.c
	$(CC) -o $@ $< $(CFLAGS)

byteorder: byteorder.c
	$(CC) -o $@ $< $(CFLAGS)

.PHONY: clean

clean:
	rm -f daytimetcpcli daytimetcpsrv daytimetcpsrv1 byteorder
