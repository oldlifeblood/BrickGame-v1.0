CC = g++ -std=c++17

all: install

install: uninstall
	mkdir Game
	mkdir Game/cli
	mkdir Game/desktop
	touch Game/cli/high_score_tetris.txt
	touch Game/desktop/high_score_tetris.txt
	touch Game/desktop/high_score_snake.txt
	echo "0" >> Game/cli/high_score_tetris.txt
	echo "0" >> Game/desktop/high_score_tetris.txt
	echo "0" >> Game/desktop/high_score_snake.txt
	cd Game/desktop/ && qmake ../../gui/desktop/brickgame && make
	g++ brick_game/tetris/s21_tetris.c brick_game/snake/*.cc gui/cli/*.cc -o Game/cli/BrickGame -lncurses -std=c++17

uninstall:
	rm -rf Game

test: clean
	$(CC) tests/test_snake.cc brick_game/snake/s21_controller.cc brick_game/snake/s21_model.cc -o tests/testing -lgtest -pthread
	./tests/testing

cli_start:
	cd Game/cli && ./BrickGame

desktop_start:
	cd Game/desktop && brickgame.app/Contents/MacOS/brickgame

gcov_report: clean
	$(CC) tests/test_snake.cc brick_game/snake/s21_controller.cc brick_game/snake/s21_model.cc -o tests/testing -lgtest -pthread --coverage
	./tests/testing
	lcov --exclude '/usr/local/include/gtest/*' --exclude 'v1/*' -d ./ --capture --output-file snake.info --ignore-errors mismatch --ignore-errors inconsistent
	genhtml snake.info --output-directory report --ignore-errors inconsistent
	open report/index.html
	rm -rf high_score_snake.txt
	
dist: uninstall install
	tar cvzf Snake.tgz Game/

dvi:
	doxygen Doxyfile
	open html/index.html

clang-check:
	cp ../materials/linters/.clang-format .
	clang-format -n brick_game/snake/*.cc brick_game/snake/*.h brick_game/tetris/*.h brick_game/tetris/*.c gui/cli/*.cc gui/cli/*.h gui/desktop/brick_game/*.cpp gui/desktop/brick_game/*.h tests/*.cc tests/*.c
	rm ./.clang-format

clang-formatting:
	cp ../materials/linters/.clang-format .
	clang-format -i brick_game/snake/*.cc brick_game/snake/*.h brick_game/tetris/*.h brick_game/tetris/*.c gui/cli/*.cc gui/cli/*.h gui/desktop/brick_game/*.cpp gui/desktop/brick_game/*.h tests/*.cc tests/*.c
	rm ./.clang-format

clean:
	rm -rf Game/
	rm -rf *.a *.out *.o test *.html *.css
	rm -rf *.g* *.info report *.txt *.tgz
	rm -rf tests/testing tests/*.gcda tests/*.gcno snake.info report
	rm -rf high_score_tetris.txt high_score_snake.txt
	rm -rf html latex