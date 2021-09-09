include ../Make.defines.in

daytimetcpcli: daytimetcpcli.c
	$(CC) -o $@ $< $(CFLAGS)

daytimetcpsrv: daytimetcpsrv.c
	$(CC) -o $@ $< $(CFLAGS)

.PHONY: clean

clean:
	rm -f daytimetcpcli daytimetcpsrv
