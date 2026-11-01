include("${CMAKE_CURRENT_LIST_DIR}/rule.cmake")
include("${CMAKE_CURRENT_LIST_DIR}/file.cmake")

set(test4_default_library_list )

set(OUTPUT_SUFFIX elf)
# Handle files with suffix s, for group default-XC-DSC
if(test4_default_default_XC_DSC_FILE_TYPE_assemble)
add_library(test4_default_default_XC_DSC_assemble OBJECT ${test4_default_default_XC_DSC_FILE_TYPE_assemble})
    test4_default_default_XC_DSC_assemble_rule(test4_default_default_XC_DSC_assemble)
    list(APPEND test4_default_library_list "$<TARGET_OBJECTS:test4_default_default_XC_DSC_assemble>")

endif()

# Handle files with suffix S, for group default-XC-DSC
if(test4_default_default_XC_DSC_FILE_TYPE_assemblePreproc)
add_library(test4_default_default_XC_DSC_assemblePreproc OBJECT ${test4_default_default_XC_DSC_FILE_TYPE_assemblePreproc})
    test4_default_default_XC_DSC_assemblePreproc_rule(test4_default_default_XC_DSC_assemblePreproc)
    list(APPEND test4_default_library_list "$<TARGET_OBJECTS:test4_default_default_XC_DSC_assemblePreproc>")

endif()

# Handle files with suffix c, for group default-XC-DSC
if(test4_default_default_XC_DSC_FILE_TYPE_compile)
add_library(test4_default_default_XC_DSC_compile OBJECT ${test4_default_default_XC_DSC_FILE_TYPE_compile})
    test4_default_default_XC_DSC_compile_rule(test4_default_default_XC_DSC_compile)
    list(APPEND test4_default_library_list "$<TARGET_OBJECTS:test4_default_default_XC_DSC_compile>")

endif()

# Handle files with suffix cpp, for group default-XC-DSC
if(test4_default_default_XC_DSC_FILE_TYPE_compile_cpp)
add_library(test4_default_default_XC_DSC_compile_cpp OBJECT ${test4_default_default_XC_DSC_FILE_TYPE_compile_cpp})
    test4_default_default_XC_DSC_compile_cpp_rule(test4_default_default_XC_DSC_compile_cpp)
    list(APPEND test4_default_library_list "$<TARGET_OBJECTS:test4_default_default_XC_DSC_compile_cpp>")

endif()

# Handle files with suffix s, for group default-XC-DSC
if(test4_default_default_XC_DSC_FILE_TYPE_dependentObject)
add_library(test4_default_default_XC_DSC_dependentObject OBJECT ${test4_default_default_XC_DSC_FILE_TYPE_dependentObject})
    test4_default_default_XC_DSC_dependentObject_rule(test4_default_default_XC_DSC_dependentObject)
    list(APPEND test4_default_library_list "$<TARGET_OBJECTS:test4_default_default_XC_DSC_dependentObject>")

endif()

# Handle files with suffix elf, for group default-XC-DSC
if(test4_default_default_XC_DSC_FILE_TYPE_bin2hex)
add_library(test4_default_default_XC_DSC_bin2hex OBJECT ${test4_default_default_XC_DSC_FILE_TYPE_bin2hex})
    test4_default_default_XC_DSC_bin2hex_rule(test4_default_default_XC_DSC_bin2hex)
    list(APPEND test4_default_library_list "$<TARGET_OBJECTS:test4_default_default_XC_DSC_bin2hex>")

endif()

# Handle files with suffix elf, for group default-XC-DSC
if(test4_default_default_XC_DSC_FILE_TYPE_objcopy_lss)
add_library(test4_default_default_XC_DSC_objcopy_lss OBJECT ${test4_default_default_XC_DSC_FILE_TYPE_objcopy_lss})
    test4_default_default_XC_DSC_objcopy_lss_rule(test4_default_default_XC_DSC_objcopy_lss)
    list(APPEND test4_default_library_list "$<TARGET_OBJECTS:test4_default_default_XC_DSC_objcopy_lss>")

endif()


# Main target for this project
add_executable(test4_default_image_t0BQtNl0 ${test4_default_library_list})

if(NOT CMAKE_HOST_WIN32)
    set_target_properties(test4_default_image_t0BQtNl0 PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${test4_default_output_dir}")
endif()
set_target_properties(test4_default_image_t0BQtNl0 PROPERTIES
    OUTPUT_NAME "default"
    SUFFIX ".elf")
target_link_libraries(test4_default_image_t0BQtNl0 PRIVATE ${test4_default_default_XC_DSC_FILE_TYPE_link})
# Add the link options from the rule file.
test4_default_link_rule( test4_default_image_t0BQtNl0)

# Call bin2hex function from the rule file
test4_default_bin2hex_rule(test4_default_image_t0BQtNl0)
if(CMAKE_HOST_WIN32)
    add_custom_command(
        TARGET test4_default_image_t0BQtNl0
        POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E make_directory ${test4_default_output_dir}
        COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:test4_default_image_t0BQtNl0> ${test4_default_output_dir}/${test4_default_image_name}
        BYPRODUCTS ${test4_default_output_dir}/${test4_default_image_name}
        COMMENT "Copying elf to out location")
    set_property(
        TARGET test4_default_image_t0BQtNl0
        APPEND PROPERTY ADDITIONAL_CLEAN_FILES
        ${test4_default_output_dir}/${test4_default_image_name})
endif()

#Add objcopy steps
test4_default_objcopy_lss_rule(test4_default_image_t0BQtNl0)

