add_library(adder STATIC adder.cpp)
install(TARGETS adder DESTINATION lib CONFIGURATIONS Debug)
install(FILES adder.h DESTINATION include)