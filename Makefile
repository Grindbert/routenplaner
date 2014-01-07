#############################################################################
# Makefile for building: Route
# Generated by qmake (3.0) (Qt 5.1.1) on: Di. Jan. 7 19:48:17 2014
# Project:  Route.pro
# Template: app
# Command: /home/grindbert/Qt5.1.1/5.1.1/gcc_64/bin/qmake CONFIG+=debug_and_release CONFIG+=debug -spec linux-g++ -o Makefile Route.pro
#############################################################################

MAKEFILE      = Makefile

first: debug
install: debug-install
uninstall: debug-uninstall
QMAKE         = /home/grindbert/Qt5.1.1/5.1.1/gcc_64/bin/qmake
DEL_FILE      = rm -f
CHK_DIR_EXISTS= test -d
MKDIR         = mkdir -p
COPY          = cp -f
COPY_FILE     = cp -f
COPY_DIR      = cp -f -R
INSTALL_FILE  = install -m 644 -p
INSTALL_PROGRAM = install -m 755 -p
INSTALL_DIR   = $(COPY_DIR)
DEL_FILE      = rm -f
SYMLINK       = ln -f -s
DEL_DIR       = rmdir
MOVE          = mv -f
SUBTARGETS    =  \
		debug \
		release


debug: FORCE
	$(MAKE) -f $(MAKEFILE).Debug
debug-make_first: FORCE
	$(MAKE) -f $(MAKEFILE).Debug 
debug-all: FORCE
	$(MAKE) -f $(MAKEFILE).Debug all
debug-clean: FORCE
	$(MAKE) -f $(MAKEFILE).Debug clean
debug-distclean: FORCE
	$(MAKE) -f $(MAKEFILE).Debug distclean
debug-install: FORCE
	$(MAKE) -f $(MAKEFILE).Debug install
debug-uninstall: FORCE
	$(MAKE) -f $(MAKEFILE).Debug uninstall
release: FORCE
	$(MAKE) -f $(MAKEFILE).Release
release-make_first: FORCE
	$(MAKE) -f $(MAKEFILE).Release 
release-all: FORCE
	$(MAKE) -f $(MAKEFILE).Release all
release-clean: FORCE
	$(MAKE) -f $(MAKEFILE).Release clean
release-distclean: FORCE
	$(MAKE) -f $(MAKEFILE).Release distclean
release-install: FORCE
	$(MAKE) -f $(MAKEFILE).Release install
release-uninstall: FORCE
	$(MAKE) -f $(MAKEFILE).Release uninstall

Makefile: Route.pro /home/grindbert/Qt5.1.1/5.1.1/gcc_64/mkspecs/linux-g++/qmake.conf /home/grindbert/Qt5.1.1/5.1.1/gcc_64/mkspecs/features/spec_pre.prf \
		/home/grindbert/Qt5.1.1/5.1.1/gcc_64/mkspecs/common/shell-unix.conf \
		/home/grindbert/Qt5.1.1/5.1.1/gcc_64/mkspecs/common/unix.conf \
		/home/grindbert/Qt5.1.1/5.1.1/gcc_64/mkspecs/common/linux.conf \
		/home/grindbert/Qt5.1.1/5.1.1/gcc_64/mkspecs/common/gcc-base.conf \
		/home/grindbert/Qt5.1.1/5.1.1/gcc_64/mkspecs/common/gcc-base-unix.conf \
		/home/grindbert/Qt5.1.1/5.1.1/gcc_64/mkspecs/common/g++-base.conf \
		/home/grindbert/Qt5.1.1/5.1.1/gcc_64/mkspecs/common/g++-unix.conf \
		/home/grindbert/Qt5.1.1/5.1.1/gcc_64/mkspecs/qconfig.pri \
		/home/grindbert/Qt5.1.1/5.1.1/gcc_64/mkspecs/modules/qt_lib_clucene.pri \
		/home/grindbert/Qt5.1.1/5.1.1/gcc_64/mkspecs/modules/qt_lib_concurrent.pri \
		/home/grindbert/Qt5.1.1/5.1.1/gcc_64/mkspecs/modules/qt_lib_core.pri \
		/home/grindbert/Qt5.1.1/5.1.1/gcc_64/mkspecs/modules/qt_lib_dbus.pri \
		/home/grindbert/Qt5.1.1/5.1.1/gcc_64/mkspecs/modules/qt_lib_declarative.pri \
		/home/grindbert/Qt5.1.1/5.1.1/gcc_64/mkspecs/modules/qt_lib_designer.pri \
		/home/grindbert/Qt5.1.1/5.1.1/gcc_64/mkspecs/modules/qt_lib_designercomponents.pri \
		/home/grindbert/Qt5.1.1/5.1.1/gcc_64/mkspecs/modules/qt_lib_gui.pri \
		/home/grindbert/Qt5.1.1/5.1.1/gcc_64/mkspecs/modules/qt_lib_help.pri \
		/home/grindbert/Qt5.1.1/5.1.1/gcc_64/mkspecs/modules/qt_lib_multimedia.pri \
		/home/grindbert/Qt5.1.1/5.1.1/gcc_64/mkspecs/modules/qt_lib_multimediawidgets.pri \
		/home/grindbert/Qt5.1.1/5.1.1/gcc_64/mkspecs/modules/qt_lib_network.pri \
		/home/grindbert/Qt5.1.1/5.1.1/gcc_64/mkspecs/modules/qt_lib_opengl.pri \
		/home/grindbert/Qt5.1.1/5.1.1/gcc_64/mkspecs/modules/qt_lib_openglextensions.pri \
		/home/grindbert/Qt5.1.1/5.1.1/gcc_64/mkspecs/modules/qt_lib_platformsupport.pri \
		/home/grindbert/Qt5.1.1/5.1.1/gcc_64/mkspecs/modules/qt_lib_printsupport.pri \
		/home/grindbert/Qt5.1.1/5.1.1/gcc_64/mkspecs/modules/qt_lib_qml.pri \
		/home/grindbert/Qt5.1.1/5.1.1/gcc_64/mkspecs/modules/qt_lib_qmldevtools.pri \
		/home/grindbert/Qt5.1.1/5.1.1/gcc_64/mkspecs/modules/qt_lib_qmltest.pri \
		/home/grindbert/Qt5.1.1/5.1.1/gcc_64/mkspecs/modules/qt_lib_qtmultimediaquicktools.pri \
		/home/grindbert/Qt5.1.1/5.1.1/gcc_64/mkspecs/modules/qt_lib_quick.pri \
		/home/grindbert/Qt5.1.1/5.1.1/gcc_64/mkspecs/modules/qt_lib_quickparticles.pri \
		/home/grindbert/Qt5.1.1/5.1.1/gcc_64/mkspecs/modules/qt_lib_script.pri \
		/home/grindbert/Qt5.1.1/5.1.1/gcc_64/mkspecs/modules/qt_lib_scripttools.pri \
		/home/grindbert/Qt5.1.1/5.1.1/gcc_64/mkspecs/modules/qt_lib_sensors.pri \
		/home/grindbert/Qt5.1.1/5.1.1/gcc_64/mkspecs/modules/qt_lib_serialport.pri \
		/home/grindbert/Qt5.1.1/5.1.1/gcc_64/mkspecs/modules/qt_lib_sql.pri \
		/home/grindbert/Qt5.1.1/5.1.1/gcc_64/mkspecs/modules/qt_lib_svg.pri \
		/home/grindbert/Qt5.1.1/5.1.1/gcc_64/mkspecs/modules/qt_lib_testlib.pri \
		/home/grindbert/Qt5.1.1/5.1.1/gcc_64/mkspecs/modules/qt_lib_uitools.pri \
		/home/grindbert/Qt5.1.1/5.1.1/gcc_64/mkspecs/modules/qt_lib_v8.pri \
		/home/grindbert/Qt5.1.1/5.1.1/gcc_64/mkspecs/modules/qt_lib_webkit.pri \
		/home/grindbert/Qt5.1.1/5.1.1/gcc_64/mkspecs/modules/qt_lib_webkitwidgets.pri \
		/home/grindbert/Qt5.1.1/5.1.1/gcc_64/mkspecs/modules/qt_lib_widgets.pri \
		/home/grindbert/Qt5.1.1/5.1.1/gcc_64/mkspecs/modules/qt_lib_x11extras.pri \
		/home/grindbert/Qt5.1.1/5.1.1/gcc_64/mkspecs/modules/qt_lib_xml.pri \
		/home/grindbert/Qt5.1.1/5.1.1/gcc_64/mkspecs/modules/qt_lib_xmlpatterns.pri \
		/home/grindbert/Qt5.1.1/5.1.1/gcc_64/mkspecs/features/qt_functions.prf \
		/home/grindbert/Qt5.1.1/5.1.1/gcc_64/mkspecs/features/qt_config.prf \
		/home/grindbert/Qt5.1.1/5.1.1/gcc_64/mkspecs/linux-g++/qmake.conf \
		/home/grindbert/Qt5.1.1/5.1.1/gcc_64/mkspecs/features/spec_post.prf \
		/home/grindbert/Qt5.1.1/5.1.1/gcc_64/mkspecs/features/exclusive_builds.prf \
		/home/grindbert/Qt5.1.1/5.1.1/gcc_64/mkspecs/features/default_pre.prf \
		/home/grindbert/Qt5.1.1/5.1.1/gcc_64/mkspecs/features/unix/default_pre.prf \
		/home/grindbert/Qt5.1.1/5.1.1/gcc_64/mkspecs/features/resolve_config.prf \
		/home/grindbert/Qt5.1.1/5.1.1/gcc_64/mkspecs/features/default_post.prf \
		/home/grindbert/Qt5.1.1/5.1.1/gcc_64/mkspecs/features/unix/gdb_dwarf_index.prf \
		/home/grindbert/Qt5.1.1/5.1.1/gcc_64/mkspecs/features/warn_on.prf \
		/home/grindbert/Qt5.1.1/5.1.1/gcc_64/mkspecs/features/qt.prf \
		/home/grindbert/Qt5.1.1/5.1.1/gcc_64/mkspecs/features/resources.prf \
		/home/grindbert/Qt5.1.1/5.1.1/gcc_64/mkspecs/features/moc.prf \
		/home/grindbert/Qt5.1.1/5.1.1/gcc_64/mkspecs/features/unix/opengl.prf \
		/home/grindbert/Qt5.1.1/5.1.1/gcc_64/mkspecs/features/uic.prf \
		/home/grindbert/Qt5.1.1/5.1.1/gcc_64/mkspecs/features/unix/thread.prf \
		/home/grindbert/Qt5.1.1/5.1.1/gcc_64/mkspecs/features/wayland-scanner.prf \
		/home/grindbert/Qt5.1.1/5.1.1/gcc_64/mkspecs/features/testcase_targets.prf \
		/home/grindbert/Qt5.1.1/5.1.1/gcc_64/mkspecs/features/exceptions.prf \
		/home/grindbert/Qt5.1.1/5.1.1/gcc_64/mkspecs/features/yacc.prf \
		/home/grindbert/Qt5.1.1/5.1.1/gcc_64/mkspecs/features/lex.prf \
		Route.pro \
		/home/grindbert/Qt5.1.1/5.1.1/gcc_64/lib/libQt5Widgets.prl \
		/home/grindbert/Qt5.1.1/5.1.1/gcc_64/lib/libQt5Network.prl \
		/home/grindbert/Qt5.1.1/5.1.1/gcc_64/lib/libQt5Gui.prl \
		/home/grindbert/Qt5.1.1/5.1.1/gcc_64/lib/libQt5Core.prl
	$(QMAKE) CONFIG+=debug_and_release CONFIG+=debug -spec linux-g++ -o Makefile Route.pro
/home/grindbert/Qt5.1.1/5.1.1/gcc_64/mkspecs/features/spec_pre.prf:
/home/grindbert/Qt5.1.1/5.1.1/gcc_64/mkspecs/common/shell-unix.conf:
/home/grindbert/Qt5.1.1/5.1.1/gcc_64/mkspecs/common/unix.conf:
/home/grindbert/Qt5.1.1/5.1.1/gcc_64/mkspecs/common/linux.conf:
/home/grindbert/Qt5.1.1/5.1.1/gcc_64/mkspecs/common/gcc-base.conf:
/home/grindbert/Qt5.1.1/5.1.1/gcc_64/mkspecs/common/gcc-base-unix.conf:
/home/grindbert/Qt5.1.1/5.1.1/gcc_64/mkspecs/common/g++-base.conf:
/home/grindbert/Qt5.1.1/5.1.1/gcc_64/mkspecs/common/g++-unix.conf:
/home/grindbert/Qt5.1.1/5.1.1/gcc_64/mkspecs/qconfig.pri:
/home/grindbert/Qt5.1.1/5.1.1/gcc_64/mkspecs/modules/qt_lib_clucene.pri:
/home/grindbert/Qt5.1.1/5.1.1/gcc_64/mkspecs/modules/qt_lib_concurrent.pri:
/home/grindbert/Qt5.1.1/5.1.1/gcc_64/mkspecs/modules/qt_lib_core.pri:
/home/grindbert/Qt5.1.1/5.1.1/gcc_64/mkspecs/modules/qt_lib_dbus.pri:
/home/grindbert/Qt5.1.1/5.1.1/gcc_64/mkspecs/modules/qt_lib_declarative.pri:
/home/grindbert/Qt5.1.1/5.1.1/gcc_64/mkspecs/modules/qt_lib_designer.pri:
/home/grindbert/Qt5.1.1/5.1.1/gcc_64/mkspecs/modules/qt_lib_designercomponents.pri:
/home/grindbert/Qt5.1.1/5.1.1/gcc_64/mkspecs/modules/qt_lib_gui.pri:
/home/grindbert/Qt5.1.1/5.1.1/gcc_64/mkspecs/modules/qt_lib_help.pri:
/home/grindbert/Qt5.1.1/5.1.1/gcc_64/mkspecs/modules/qt_lib_multimedia.pri:
/home/grindbert/Qt5.1.1/5.1.1/gcc_64/mkspecs/modules/qt_lib_multimediawidgets.pri:
/home/grindbert/Qt5.1.1/5.1.1/gcc_64/mkspecs/modules/qt_lib_network.pri:
/home/grindbert/Qt5.1.1/5.1.1/gcc_64/mkspecs/modules/qt_lib_opengl.pri:
/home/grindbert/Qt5.1.1/5.1.1/gcc_64/mkspecs/modules/qt_lib_openglextensions.pri:
/home/grindbert/Qt5.1.1/5.1.1/gcc_64/mkspecs/modules/qt_lib_platformsupport.pri:
/home/grindbert/Qt5.1.1/5.1.1/gcc_64/mkspecs/modules/qt_lib_printsupport.pri:
/home/grindbert/Qt5.1.1/5.1.1/gcc_64/mkspecs/modules/qt_lib_qml.pri:
/home/grindbert/Qt5.1.1/5.1.1/gcc_64/mkspecs/modules/qt_lib_qmldevtools.pri:
/home/grindbert/Qt5.1.1/5.1.1/gcc_64/mkspecs/modules/qt_lib_qmltest.pri:
/home/grindbert/Qt5.1.1/5.1.1/gcc_64/mkspecs/modules/qt_lib_qtmultimediaquicktools.pri:
/home/grindbert/Qt5.1.1/5.1.1/gcc_64/mkspecs/modules/qt_lib_quick.pri:
/home/grindbert/Qt5.1.1/5.1.1/gcc_64/mkspecs/modules/qt_lib_quickparticles.pri:
/home/grindbert/Qt5.1.1/5.1.1/gcc_64/mkspecs/modules/qt_lib_script.pri:
/home/grindbert/Qt5.1.1/5.1.1/gcc_64/mkspecs/modules/qt_lib_scripttools.pri:
/home/grindbert/Qt5.1.1/5.1.1/gcc_64/mkspecs/modules/qt_lib_sensors.pri:
/home/grindbert/Qt5.1.1/5.1.1/gcc_64/mkspecs/modules/qt_lib_serialport.pri:
/home/grindbert/Qt5.1.1/5.1.1/gcc_64/mkspecs/modules/qt_lib_sql.pri:
/home/grindbert/Qt5.1.1/5.1.1/gcc_64/mkspecs/modules/qt_lib_svg.pri:
/home/grindbert/Qt5.1.1/5.1.1/gcc_64/mkspecs/modules/qt_lib_testlib.pri:
/home/grindbert/Qt5.1.1/5.1.1/gcc_64/mkspecs/modules/qt_lib_uitools.pri:
/home/grindbert/Qt5.1.1/5.1.1/gcc_64/mkspecs/modules/qt_lib_v8.pri:
/home/grindbert/Qt5.1.1/5.1.1/gcc_64/mkspecs/modules/qt_lib_webkit.pri:
/home/grindbert/Qt5.1.1/5.1.1/gcc_64/mkspecs/modules/qt_lib_webkitwidgets.pri:
/home/grindbert/Qt5.1.1/5.1.1/gcc_64/mkspecs/modules/qt_lib_widgets.pri:
/home/grindbert/Qt5.1.1/5.1.1/gcc_64/mkspecs/modules/qt_lib_x11extras.pri:
/home/grindbert/Qt5.1.1/5.1.1/gcc_64/mkspecs/modules/qt_lib_xml.pri:
/home/grindbert/Qt5.1.1/5.1.1/gcc_64/mkspecs/modules/qt_lib_xmlpatterns.pri:
/home/grindbert/Qt5.1.1/5.1.1/gcc_64/mkspecs/features/qt_functions.prf:
/home/grindbert/Qt5.1.1/5.1.1/gcc_64/mkspecs/features/qt_config.prf:
/home/grindbert/Qt5.1.1/5.1.1/gcc_64/mkspecs/linux-g++/qmake.conf:
/home/grindbert/Qt5.1.1/5.1.1/gcc_64/mkspecs/features/spec_post.prf:
/home/grindbert/Qt5.1.1/5.1.1/gcc_64/mkspecs/features/exclusive_builds.prf:
/home/grindbert/Qt5.1.1/5.1.1/gcc_64/mkspecs/features/default_pre.prf:
/home/grindbert/Qt5.1.1/5.1.1/gcc_64/mkspecs/features/unix/default_pre.prf:
/home/grindbert/Qt5.1.1/5.1.1/gcc_64/mkspecs/features/resolve_config.prf:
/home/grindbert/Qt5.1.1/5.1.1/gcc_64/mkspecs/features/default_post.prf:
/home/grindbert/Qt5.1.1/5.1.1/gcc_64/mkspecs/features/unix/gdb_dwarf_index.prf:
/home/grindbert/Qt5.1.1/5.1.1/gcc_64/mkspecs/features/warn_on.prf:
/home/grindbert/Qt5.1.1/5.1.1/gcc_64/mkspecs/features/qt.prf:
/home/grindbert/Qt5.1.1/5.1.1/gcc_64/mkspecs/features/resources.prf:
/home/grindbert/Qt5.1.1/5.1.1/gcc_64/mkspecs/features/moc.prf:
/home/grindbert/Qt5.1.1/5.1.1/gcc_64/mkspecs/features/unix/opengl.prf:
/home/grindbert/Qt5.1.1/5.1.1/gcc_64/mkspecs/features/uic.prf:
/home/grindbert/Qt5.1.1/5.1.1/gcc_64/mkspecs/features/unix/thread.prf:
/home/grindbert/Qt5.1.1/5.1.1/gcc_64/mkspecs/features/wayland-scanner.prf:
/home/grindbert/Qt5.1.1/5.1.1/gcc_64/mkspecs/features/testcase_targets.prf:
/home/grindbert/Qt5.1.1/5.1.1/gcc_64/mkspecs/features/exceptions.prf:
/home/grindbert/Qt5.1.1/5.1.1/gcc_64/mkspecs/features/yacc.prf:
/home/grindbert/Qt5.1.1/5.1.1/gcc_64/mkspecs/features/lex.prf:
Route.pro:
/home/grindbert/Qt5.1.1/5.1.1/gcc_64/lib/libQt5Widgets.prl:
/home/grindbert/Qt5.1.1/5.1.1/gcc_64/lib/libQt5Network.prl:
/home/grindbert/Qt5.1.1/5.1.1/gcc_64/lib/libQt5Gui.prl:
/home/grindbert/Qt5.1.1/5.1.1/gcc_64/lib/libQt5Core.prl:
qmake: FORCE
	@$(QMAKE) CONFIG+=debug_and_release CONFIG+=debug -spec linux-g++ -o Makefile Route.pro

qmake_all: FORCE

make_first: debug-make_first release-make_first FORCE
all: debug-all release-all FORCE
clean: debug-clean release-clean FORCE
distclean: debug-distclean release-distclean FORCE
	-$(DEL_FILE) Makefile

debug-mocclean:
	$(MAKE) -f $(MAKEFILE).Debug mocclean
release-mocclean:
	$(MAKE) -f $(MAKEFILE).Release mocclean
mocclean: debug-mocclean release-mocclean

debug-mocables:
	$(MAKE) -f $(MAKEFILE).Debug mocables
release-mocables:
	$(MAKE) -f $(MAKEFILE).Release mocables
mocables: debug-mocables release-mocables

check: first
FORCE:

$(MAKEFILE).Debug: Makefile
$(MAKEFILE).Release: Makefile
