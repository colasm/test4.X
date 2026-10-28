set(DEPENDENT_MP_BIN2HEXtest4_default_t0BQtNl0 "C:/Users/Maxime COLAS/.mplab/app-finder/shims/xc-dsc/3.21/xc-dsc-bin2hex.exe")
set(DEPENDENT_DEPENDENT_TARGET_ELFtest4_default_t0BQtNl0 "${CMAKE_CURRENT_LIST_DIR}/../../../../out/test4/default.elf")
set(DEPENDENT_TARGET_DIRtest4_default_t0BQtNl0 "${CMAKE_CURRENT_LIST_DIR}/../../../../out/test4")
set(DEPENDENT_BYPRODUCTStest4_default_t0BQtNl0 ${DEPENDENT_TARGET_DIRtest4_default_t0BQtNl0}/${sourceFileNametest4_default_t0BQtNl0}.s)
add_custom_command(
    OUTPUT ${DEPENDENT_TARGET_DIRtest4_default_t0BQtNl0}/${sourceFileNametest4_default_t0BQtNl0}.s
    COMMAND ${DEPENDENT_MP_BIN2HEXtest4_default_t0BQtNl0} ${DEPENDENT_DEPENDENT_TARGET_ELFtest4_default_t0BQtNl0} --image ${sourceFileNametest4_default_t0BQtNl0} ${addresstest4_default_t0BQtNl0} ${modetest4_default_t0BQtNl0} -mdfp=C:/Users/Maxime COLAS/.mchp_packs/Microchip/dsPIC33AK-MC_DFP/1.1.109/xc16 
    WORKING_DIRECTORY ${DEPENDENT_TARGET_DIRtest4_default_t0BQtNl0}
    DEPENDS ${DEPENDENT_DEPENDENT_TARGET_ELFtest4_default_t0BQtNl0})
add_custom_target(
    dependent_produced_source_artifacttest4_default_t0BQtNl0 
    DEPENDS ${DEPENDENT_TARGET_DIRtest4_default_t0BQtNl0}/${sourceFileNametest4_default_t0BQtNl0}.s
    )
