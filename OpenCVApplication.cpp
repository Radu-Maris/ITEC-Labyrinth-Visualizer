#include "stdafx.h"
#include "common.h"
#include <opencv2/core/utils/logger.hpp>
#include <iostream>
#include <fstream>
#include <stdio.h>
#include <Windows.h>
#include <opencv2/highgui/highgui.hpp>  // Video write
#include <opencv2/core/core.hpp>        // Basic OpenCV structures (cv::Mat)

wchar_t* projectPath;

using namespace std;

void maze() {
	string myText;
	
	std::ifstream file("Images/Model_maze.txt");

	int starti, startj, dir, walls_0, walls_1, walls_2, walls_3, moved_ok =0;
	
	file >> starti >> startj;

	Mat_<Vec3b> dst(500, 800);
	dst.setTo(Scalar(200, 200, 200));

	int di[] = { -20, 0, 20,  0};
	int dj[] = {  0, 20, 0, -20};

	int pos_ant_i, pos_ant_j, first_iteration = 0;

	for (int i = starti - 9; i <= starti + 9; i++) {
		for (int j = startj - 9; j <= startj + 9; j++) {
			dst(i, j) = Vec3b(0, 255, 0);
		}
	}

	while (file) {
		file >> dir;

		file >> walls_0;
		file >> walls_1;
		file >> walls_2;
		file >> walls_3;

		file >> moved_ok;

		if (first_iteration != 0) {
			for (int i = pos_ant_i - 9; i <= pos_ant_i + 9; i++) {
				for (int j = pos_ant_j - 9; j <= pos_ant_j + 9; j++) {
					dst(i, j) = Vec3b(0, 255, 0);
				}
			}
		}

		for (int i = starti - 9; i <= starti + 9; i++) {
			for (int j = startj - 9; j <= startj + 9; j++) {
				dst(i, j) = Vec3b(170, 100, 0);
			}
		}

		first_iteration++;

		pos_ant_i = starti;
		pos_ant_j = startj;

		std::cout << first_iteration<<": " << walls_0 << " " << walls_1 << " " << walls_2 << " " << walls_3 << endl;
		if (moved_ok == 1) {
			if (walls_0 == 0) {
				for (int i = startj - 10; i <= startj + 10; i++)
					dst(starti + di[0] / 2, i + dj[0] / 2) = Vec3b(0, 0, 0);
			}
			else {
				for (int i = startj - 8; i <= startj + 8; i++)
					dst(starti + di[0] / 2, i + dj[0] / 2) = Vec3b(0, 255, 0);
			}

			if (walls_1 == 0) {
				for (int i = starti - 10; i <= starti + 10; i++)
					dst(i + di[1] / 2, startj + dj[1] / 2) = Vec3b(0, 0, 0);
			}
			else {
				for (int i = starti - 8; i <= starti + 8; i++)
					dst(i + di[1] / 2, startj + dj[1] / 2) = Vec3b(0, 255, 0);
			}

			if (walls_2 == 0) {
				for (int i = startj - 10; i <= startj + 10; i++)
					dst(starti + di[2] / 2, i + dj[2] / 2) = Vec3b(0, 0, 0);
			}
			else {
				for (int i = startj - 8; i <= startj + 8; i++)
					dst(starti + di[2] / 2, i + dj[2] / 2) = Vec3b(0, 255, 0);
			}

			if (walls_3 == 0) {
				for (int i = starti - 10; i <= starti + 10; i++)
					dst(i + di[3] / 2, startj + dj[3] / 2) = Vec3b(0, 0, 0);
			}
			else {
				for (int i = starti - 8; i <= starti + 8; i++)
					dst(i + di[3] / 2, startj + dj[3] / 2) = Vec3b(0, 255, 0);
			}

			
			starti = starti + di[dir];
			startj = startj + dj[dir];

		}
		
		
		for (;;)
		{
			imshow("frame", dst);
			if (waitKey(30) >= 0) 
				break;
		}
		

		destroyAllWindows();

	}

	imshow("Final", dst);
	waitKey();
}

int main() 
{
	cv::utils::logging::setLogLevel(cv::utils::logging::LOG_LEVEL_FATAL);
    projectPath = _wgetcwd(0, 0);

	int op;
	do
	{
		system("cls");
		destroyAllWindows();
		printf("Menu:\n");
		printf(" 1 - Open image\n");
		printf(" 0 - Exit\n\n");
		printf("Option: ");
		scanf("%d",&op);
		switch (op)
		{
		case 1:
			maze();
			break;
		}
	}
	while (op!=0);
	return 0;
}