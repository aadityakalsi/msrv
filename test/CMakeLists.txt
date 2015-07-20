# TEST: proj test sub module

add_test_exe    (tversion tversion.c)
test_link_libs  (tversion msrv)
create_test     (tversion)

add_exe         (hleak hleak.c)
link_libs       (hleak msrv)
install_tgt     (hleak)

add_test_exe    (talloc talloc.c)
test_link_libs  (talloc msrv)
create_test     (talloc)
add_dependencies(talloc hleak)

if (WIN32)
add_lib_build_def(talloc "_CONSOLE")
add_link_flag(talloc "/SUBSYSTEM:CONSOLE")
add_lib_build_def(talloc_install "_CONSOLE")
add_link_flag(talloc_install "/SUBSYSTEM:CONSOLE")
endif()
