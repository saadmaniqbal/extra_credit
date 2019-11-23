#include<opencv2/opencv.hpp>
#include<iostream>
#include <iostream>
#include <cmath>
#include <vector>
#include <bits/stdc++.h> 
using namespace std;
using namespace cv;



//THE PROGRAM WORKS THROUGH PIXEL AND SYNTHESIZE TO TRY TO PRODUCE AN PNG FILE OF THE TEXTURE THAT IS CREATED FROM AN INITIAL 3X3 SAMPLE



//PIXEL PROCESSES THE INDIVIDUAL COORDINATES OF THE PIXEL TO FINALLY PRODUCE AN ARRAY IN SYNTHESIZE THAT WILL PRODUCE THE FINAL IMAGE
float pixel(int x, int y, float **img_data, float **new_img_data, bool **mask, int kernel_size) {

	

	int rows = sizeof(new_img_data) / sizeof new_img_data[0];
	int col = sizeof(new_img_data[0]) / sizeof(int);

	int x0 = int(max(0, x - kernel_size));

	int y0 = int(max(0, y - kernel_size));

	int x1 = int(min(rows - 1, x + kernel_size));

	int y1 = int(min(col - 1, y + kernel_size));




	int size_x = x1 - x0;
	int size_y = y1 - y0;

	int **n_w = new int*[size_x];

	for (int i = 0; i < size_x; i++) {
		n_w[i] = new int[size_y];
	}

	for (int i = 0; i < size_x; i++) {
		for (int j = 0;j < size_y; j++) {
			n_w[i][j] = new_img_data[x0][y0];
			x0 += 1;
			y0 += 1;
		}
	}


	bool **mask_w = new bool*[size_x];

	for (int i = 0; i < size_x; i++) {
		mask_w[i] = new bool[size_y];
	}

	for (int i = 0; i < size_x; i++) {
		for (int j = 0;j < size_y; j++) {
			mask_w[i][j] = mask[x0][y0];
			x0 += 1;
			y0 += 1;
		}
	}


	int rows_len_mask = sizeof(mask) / sizeof mask[0];


	
	int rows_nw = sizeof(n_w) / sizeof n_w[0];
	int col_nw = sizeof(n_w[0]) / sizeof(int);


	
	int rows_id = sizeof(img_data) / sizeof img_data[0];
	int col_id = sizeof(img_data[0]) / sizeof(int);


	int cx = int(floor(rows_nw / 2));

	int cy = int(floor(col_nw / 2));

	vector<float> cand;

	vector<float> dist;



	for (int i = rows_nw; i < rows_id - rows_nw; i++) {
		for (int j = col_nw; i < col_id - col_nw; j++) {
			int rand_num = (rand() % (2 + 1 - 0));
			if (rand_num != 0) {
				continue;
			}

			float **sub_window = new float*[rows_nw];

			for (int a = 0; a < rows_nw; a++) {
				sub_window[a] = new float[col_nw];
			}
			int counter1, counter2 = 0;
			for (int a = 0; a < rows_nw; a++) {
				for (int b = 0;b < col_nw; b++) {
					counter1 = i;
					counter2 = j;
					sub_window[a][b] = img_data[counter1][counter2];
					counter1++;
					counter2++;
				}
			}

			float **s = new float*[rows_nw];
			for (int a = 0; a < rows_nw; a++) {
				s[a] = new float[col_nw];
			}

			for (int a = 0; a < rows_nw; a++) {
				for (int b = 0;b < col_nw; b++) {
					s[a][b] = sub_window[a][b] - n_w[a][b];

				}
			}

			//obtain an array to calculate the distance s*s*mask_window
			//and find the distance d that is the summation of 
			//the sum of all the elements divided by the length of the //mask found above

			for (int i = 0; i < rows_nw; i++) {
				for (int j = 0; j < col_nw;i++) {
					s[i][j] = s[i][j] * s[i][j];
					if (mask_w[i][j] == true) {
						s[i][j] = s[i][j] * s[i][j];
					}
					else {
						s[i][j] = 0;
					}
				}
			}

			float sum = 0;
			for (int i = 0; i < rows_nw; i++) {
				for (int j = 0; j < col_nw;i++) {
					sum += s[i][j];
				}
			}
			float d = sum / rows_len_mask;

			cand.push_back(sub_window[cx][cy]);
			dist.push_back(d);




		}
	}
	
	int sizedist = dist.size();
	vector <int> mask_n(sizedist);
	vector<int> finalcand;


	auto mini = *min_element(dist.begin(), dist.end());
	for (int a = 0; a < dist.size(); a++) {
		if ((dist[a] - mini) < 0.2) {
			mask_n[a] = true;
			finalcand.push_back(cand[a]);
		}
		else {
			mask_n[a] = false;
		}
	}

	int rand_num2;

	if (finalcand.size() < 1) {
		return 0.0;

	}
	else {
		if (finalcand.size() != 1) {
			rand_num2 = (rand() % (finalcand.size() + 1 - 0));

		}
		else {
			rand_num2 = 0;
		}
	}

	return finalcand[rand_num2];
}



//THIS IS THE HANDLER FUNCTION THAT WORKS IN CONJUNCTION WITH PIXEL ABOVE TO CREATE THE PNG FILE. THIS IS CALLED FROM THE MAIN
//FUNCTION WITH THE RELAVENT DETAILS NEEDED TO MAKE THE TEXTURE SYNTHESIS POSSIBLE.
void synthesize(int row, int col, float **img_data, int x, int y, int kernel_size) {

	int rows_idmain = row;
	int col_idmain = col;



	int size_seed_x, size_seed_y = 3;



	int seed_x = (rand() % (size_seed_x + 1 - 0));

	int seed_y = (rand() % (size_seed_y + 1 - 0));



	int **sd = new int*[size_seed_x - seed_x];
	for (int a = 0; a < (size_seed_x - seed_x); a++) {
		sd[a] = new int[size_seed_y - seed_y];
	}
	int counter1 = seed_x;
	int counter2 = seed_y;

	for (int a = 0; a < size_seed_x - seed_x; a++) {
		for (int b = 0;b < size_seed_y - seed_y; b++) {

			sd[a][b] = img_data[counter1][counter2];
			counter1++;
			counter2++;

		}
	}



	float **nid = new float*[x];
	bool **mask = new bool*[x];

	for (int a = 0; a < (x); a++) {
		nid[a] = new float[y];
		mask[a] = new bool[y];
	}

	for (int a = 0; a < x; a++) {
		for (int b = 0;b < y; b++) {

			nid[a][b] = 0;
			mask[a][b] = false;

		}
	}

	for (int a = 0; a < size_seed_x; a++) {
		for (int b = 0;b < size_seed_y; b++) {


			mask[a][b] = true;
			nid[a][b] = sd[a][b];
		}
	}


	int it = 0;

	for (int i = size_seed_x; i < x; i++) {
		int last_y = size_seed_x + it;
		for (int j = 0; j < last_y + 1;j++) {
			float v = pixel(i, j, img_data, nid, mask, kernel_size);

			nid[i][j] = v;
			mask[i][j] = true;

			for (int c = 0; c < size_seed_y + it + 1;c++) {
				float w = pixel(x, last_y, img_data, nid, mask, kernel_size);
				nid[c][last_y] = w;
				mask[c][last_y] = true;

			}
		}
		it++;
	}







	if (it % 10 == 0) {
		//this in theory will write the final image produced by the function
		imwrite("output.png", nid);
	}
}


int main() {
	Mat img = imread("input.jpg");
	
	int x, y = 256;
	int row = img.row;
	int col = img.col;
	int kernel_size = 21;

	float **array = new float*[img.rows];
	for (int i = 0; i < img.rows; ++i)
		array[i] = new float[img.cols];

	for (int i = 0; i < img.rows; ++i)
		array[i] =img.ptr<float>(i);



	synthesize(row, col, array, x, y, kernel_size / 2);
}