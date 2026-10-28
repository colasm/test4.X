# The following variables contains the files used by the different stages of the build process.
set(test4_default_default_XC_DSC_FILE_TYPE_assemble
    "${CMAKE_CURRENT_SOURCE_DIR}/../../../mcc_generated_files/system/src/dmt_asm.s"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../../mcc_generated_files/system/src/where_was_i.s"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../../signal.s")
set_source_files_properties(${test4_default_default_XC_DSC_FILE_TYPE_assemble} PROPERTIES LANGUAGE ASM)

# For assembly files, add "." to the include path for each file so that .include with a relative path works
foreach(source_file ${test4_default_default_XC_DSC_FILE_TYPE_assemble})
        set_source_files_properties(${source_file} PROPERTIES INCLUDE_DIRECTORIES "$<PATH:NORMAL_PATH,$<PATH:REMOVE_FILENAME,${source_file}>>")
endforeach()

set(test4_default_default_XC_DSC_FILE_TYPE_assemblePreproc)
set_source_files_properties(${test4_default_default_XC_DSC_FILE_TYPE_assemblePreproc} PROPERTIES LANGUAGE ASM)

# For assembly files, add "." to the include path for each file so that .include with a relative path works
foreach(source_file ${test4_default_default_XC_DSC_FILE_TYPE_assemblePreproc})
        set_source_files_properties(${source_file} PROPERTIES INCLUDE_DIRECTORIES "$<PATH:NORMAL_PATH,$<PATH:REMOVE_FILENAME,${source_file}>>")
endforeach()

set(test4_default_default_XC_DSC_FILE_TYPE_compile
    "${CMAKE_CURRENT_SOURCE_DIR}/../../../App.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../../DFR0665/AD74111.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../../DFR0665/DFR0665.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../../DFR0665/ILI9341.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../../DFR0665/XPT2046.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../../DFR0665/button.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../../DFR0665/fonts.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../../DFR0665/gfx.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../../DFR0665/switchesleds.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../../main.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../../mcc_generated_files/spi_client/src/spi2.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../../mcc_generated_files/spi_host/src/spi1.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../../mcc_generated_files/system/src/clock.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../../mcc_generated_files/system/src/config_bits.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../../mcc_generated_files/system/src/dmt.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../../mcc_generated_files/system/src/interrupt.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../../mcc_generated_files/system/src/pins.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../../mcc_generated_files/system/src/reset.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../../mcc_generated_files/system/src/system.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../../mcc_generated_files/system/src/traps.c")
set_source_files_properties(${test4_default_default_XC_DSC_FILE_TYPE_compile} PROPERTIES LANGUAGE C)
set(test4_default_default_XC_DSC_FILE_TYPE_compile_cpp)
set_source_files_properties(${test4_default_default_XC_DSC_FILE_TYPE_compile_cpp} PROPERTIES LANGUAGE CXX)
set(test4_default_default_XC_DSC_FILE_TYPE_link)
set(test4_default_default_XC_DSC_FILE_TYPE_bin2hex)
set(test4_default_default_XC_DSC_FILE_TYPE_objcopy_lss)
set(test4_default_image_name "default.elf")
set(test4_default_image_base_name "default")

# The output directory of the final image.
set(test4_default_output_dir "${CMAKE_CURRENT_SOURCE_DIR}/../../../out/test4")

# The full path to the final image.
set(test4_default_full_path_to_image ${test4_default_output_dir}/${test4_default_image_name})
