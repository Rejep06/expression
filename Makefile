# Компилятор
CXX = g++

# Флаги компиляции
CXXFLAGS = -std=c++20 -Wall -Wextra -Werror

# Флаги линковки
LDFLAGS =

# Если включена отладка
ifeq ($(DEBUG),1)
    CXXFLAGS += -g
else
    CXXFLAGS += -flto -DNDEBUG
    LDFLAGS  += -flto
endif

# Пути к заголовочным файлам
CXXFLAGS += -I $(abspath include)

# Поиск всех исходников
SOURCES := $(wildcard src/*.cpp)
OBJECTS := $(SOURCES:src/%.cpp=build/%.o)

# Итоговый исполняемый файл
EXECUTABLE = build/eval

# Главная цель
default: $(EXECUTABLE)

# Линковка
$(EXECUTABLE): $(OBJECTS)
	@printf "Linking executable $(EXECUTABLE)\n"
	$(CXX) $(LDFLAGS) $(OBJECTS) -o $@

# Компиляция всех .cpp в .o
build/%.o: src/%.cpp | build
	@printf "Building object file $@\n"
	$(CXX) -c $< $(CXXFLAGS) -o $@

# Создание папки build
build:
	mkdir -p build

# Запуск
run: $(EXECUTABLE)
	@printf "Running executable\n"
	@mkdir -p res
	@./$(EXECUTABLE) --eval "10 * (x + 4) + y * 3"

# Очистка
clean:
	@printf "Cleaning build and resource directories\n"
	rm -rf res build

.PHONY: default run clean
