DESCRIPTION = "hearth rate monitor reading the PPG sensor through the cdd_recipe"
LICENSE = "MIT"
LIC_FILES_CHKSUM = "file://${COMMON_LICENSE_DIR}/MIT;md5=0835ade698e0bcf8506ecda2f7b4f302"

SRC_URI = "file://hearthmonitor.c"

S = "${WORKDIR}"

do_compile(){
	set CFLAGS -g
	${CC} ${CFLAGS} hearthmonitor.c ${LDFLAGS} -o hearthmonitor -lm -pthread
	unset CFLAGS
}

do_install(){
	install -d ${D}${bindir}
	install -m 0755 hearthmonitor ${D}${bindir}
}
