file(GLOB user_code_srcs "./*.c")
idf_component_register(SRCS "main.c" "${user_code_srcs}"
                    INCLUDE_DIRS "." "include")
