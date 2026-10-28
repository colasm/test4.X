# The following functions contains all the flags passed to the different build stages.

set(PACK_REPO_PATH "C:/Users/Maxime COLAS/.mchp_packs" CACHE PATH "Path to the root of a pack repository.")

function(test4_default_default_XC_DSC_assemble_rule target)
    set(options
        "-g"
        "-mcpu=33AK128MC105"
        "-Wa,--defsym=__MPLAB_BUILD=1,--defsym=__MPLAB_DEBUG=1,--defsym=__DEBUG=1,-g,--no-relax"
        "-mdfp=${PACK_REPO_PATH}/Microchip/dsPIC33AK-MC_DFP/1.1.109/xc16")
    list(REMOVE_ITEM options "")
    target_compile_options(${target} PRIVATE "${options}")
    target_compile_definitions(${target}
        PRIVATE "__DEBUG=1"
        PRIVATE "XPRJ_default=default")
    target_include_directories(${target} PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/../../..")
endfunction()
function(test4_default_default_XC_DSC_assemblePreproc_rule target)
    set(options
        "-x"
        "assembler-with-cpp"
        "-g"
        "-mcpu=33AK128MC105"
        "-Wa,--defsym=__MPLAB_BUILD=1,--defsym=__MPLAB_DEBUG=1,--defsym=__DEBUG=1,-g,--no-relax"
        "-mdfp=${PACK_REPO_PATH}/Microchip/dsPIC33AK-MC_DFP/1.1.109/xc16")
    list(REMOVE_ITEM options "")
    target_compile_options(${target} PRIVATE "${options}")
    target_compile_definitions(${target}
        PRIVATE "__DEBUG=1"
        PRIVATE "XPRJ_default=default")
    target_include_directories(${target}
        PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/../../.."
        PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/../../..")
endfunction()
function(test4_default_default_XC_DSC_compile_rule target)
    set(options
        "-g"
        "-mcpu=33AK128MC105"
        "-O0"
        "-msmart-io=1"
        "-Wall"
        "-msfr-warn=off"
        "-mdfp=${PACK_REPO_PATH}/Microchip/dsPIC33AK-MC_DFP/1.1.109/xc16")
    list(REMOVE_ITEM options "")
    target_compile_options(${target} PRIVATE "${options}")
    target_compile_definitions(${target}
        PRIVATE "__DEBUG"
        PRIVATE "XPRJ_default=default"
        PRIVATE "FCY=100000000UL")
    target_include_directories(${target} PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/../../..")
endfunction()
function(test4_default_default_XC_DSC_compile_cpp_rule target)
    set(options
        "-g"
        "${CC_PRE}"
        "${DEBUGGER_NAME_AS_MACRO}"
        "-fframe-base-loclist"
        "-mcpu=33AK128MC105"
        "-frtti"
        "-fexceptions"
        "-fno-check-new"
        "-fenforce-eh-specs"
        "-fno-common"
        "-mdfp=${PACK_REPO_PATH}/Microchip/dsPIC33AK-MC_DFP/1.1.109/xc16")
    list(REMOVE_ITEM options "")
    target_compile_options(${target} PRIVATE "${options}")
    target_compile_definitions(${target}
        PRIVATE "__DEBUG"
        PRIVATE "XPRJ_default=default")
endfunction()
function(test4_default_dependentObject_rule target)
    set(options
        "-c"
        "-mcpu=33AK128MC105"
        "-mdfp=${PACK_REPO_PATH}/Microchip/dsPIC33AK-MC_DFP/1.1.109/xc16")
    list(REMOVE_ITEM options "")
    target_compile_options(${target} PRIVATE "${options}")
endfunction()
function(test4_default_link_rule target)
    set(options
        "-g"
        "-mcpu=33AK128MC105"
        "-Wl,--script=p33AK128MC105.gld,--local-stack,--defsym=__MPLAB_BUILD=1,--defsym=__MPLAB_DEBUG=1,--defsym=__DEBUG=1,-D__DEBUG=__DEBUG,--stack=16,--check-sections,--data-init,--pack-data,--handles,--isr,--no-gc-sections,--fill-upper=0,--stackguard=16,--ivt,--isr,--library-path=${CMAKE_CURRENT_SOURCE_DIR}/../../..,--no-force-link,--smart-io,--report-mem,--memorysummary,memoryfile.xml"
        "-mdfp=${PACK_REPO_PATH}/Microchip/dsPIC33AK-MC_DFP/1.1.109/xc16")
    list(REMOVE_ITEM options "")
    target_link_options(${target} PRIVATE "${options}")
    target_compile_definitions(${target}
        PRIVATE "__DEBUG=__DEBUG"
        PRIVATE "XPRJ_default=default")
endfunction()
function(test4_default_bin2hex_rule target)
    add_custom_target(
        test4_default_Bin2Hex ALL
        COMMAND ${MP_BIN2HEX} ${test4_default_image_name} -a -mdfp=${PACK_REPO_PATH}/Microchip/dsPIC33AK-MC_DFP/1.1.109/xc16
        WORKING_DIRECTORY ${test4_default_output_dir}
        BYPRODUCTS "${test4_default_output_dir}/${test4_default_image_base_name}.hex"
        COMMENT "Convert build file to .hex")
    add_dependencies(test4_default_Bin2Hex ${target})
endfunction()
function(test4_default_objcopy_lss_rule target)
    add_custom_command(
        TARGET ${target}
        POST_BUILD
        COMMAND ${OBJDUMP}
        ARGS --disassemble --wide --demangle --line-numbers --section-headers -mdfp=${PACK_REPO_PATH}/Microchip/dsPIC33AK-MC_DFP/1.1.109/xc16 --source ${test4_default_image_name} > ${test4_default_image_base_name}.lss
        WORKING_DIRECTORY ${test4_default_output_dir})
endfunction()
