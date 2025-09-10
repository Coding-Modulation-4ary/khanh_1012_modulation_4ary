#include <iostream>
// Khanh 10/12
void Encode_chiProposal46_4ary(int** PAGE, int* input_1Ddata, int PAGE_SIZE)
{
    const int BLOCK_ROWS = 256;
    const int BLOCK_COLS = 341;
    const int BITS_PER_BLOCK = 10;

    int* input = new int[BITS_PER_BLOCK];

    for (int i = 0; i < BLOCK_ROWS; i++) // 256 blocks theo chiều dọc
    {
        for (int j = 0; j < BLOCK_COLS; j++) // 341 blocks theo chiều ngang
        {
            // Lấy 10 bit đầu vào cho block này
            for (int k = 0; k < BITS_PER_BLOCK; k++)
            {
                input[k] = input_1Ddata[(i * BLOCK_COLS + j) * BITS_PER_BLOCK + k];
            }

            //if (i == 255 && j == 340)
            //{
            //    printf("===== Debug Block (i=%d, j=%d) =====\n", i, j);
            //    for (int kk = 0; kk < 4; kk++)
            //    {
            //        printf("input[%d] = %d\n", kk, input[kk]);
            //    }
            //}

            // Mapping như cũ
            PAGE[i * 4 + 0][j * 3 + 0] = input[8]; // x6
            PAGE[i * 4 + 0][j * 3 + 1] = (input[9] >> 1) % 2 + 1; // y5
            PAGE[i * 4 + 0][j * 3 + 2] = input[7]; // x4
            PAGE[i * 4 + 1][j * 3 + 0] = input[0]; // a1
            PAGE[i * 4 + 1][j * 3 + 1] = input[6]; // x3
            PAGE[i * 4 + 1][j * 3 + 2] = (input[9] % 2) + 1; // y2
            PAGE[i * 4 + 2][j * 3 + 0] = (input[4] % 2) + 1; // b2
            PAGE[i * 4 + 2][j * 3 + 1] = input[1]; // a3
            PAGE[i * 4 + 2][j * 3 + 2] = input[5]; // x1
            PAGE[i * 4 + 3][j * 3 + 0] = input[2]; // a4
            PAGE[i * 4 + 3][j * 3 + 1] = (input[4] >> 1) % 2 + 1; // b5
            PAGE[i * 4 + 3][j * 3 + 2] = input[3]; // a6
        }
    }

    delete[] input;
}

void Decode_chiProposal46_4ary(int* output_1Ddata, double** PAGE, int PAGE_SIZE)
{
    const int BLOCK_ROWS = 256;
    const int BLOCK_COLS = 341;

    for (int i = 0; i < BLOCK_ROWS; i++)
    {
        for (int j = 0; j < BLOCK_COLS; j++)
        {
            output_1Ddata[(i * BLOCK_COLS + j) * 10 + 0] = int(PAGE[i * 4 + 1][j * 3 + 0]); // a1
            output_1Ddata[(i * BLOCK_COLS + j) * 10 + 1] = int(PAGE[i * 4 + 2][j * 3 + 1]); // a3
            output_1Ddata[(i * BLOCK_COLS + j) * 10 + 2] = int(PAGE[i * 4 + 3][j * 3 + 0]); // a4
            output_1Ddata[(i * BLOCK_COLS + j) * 10 + 3] = int(PAGE[i * 4 + 3][j * 3 + 2]); // a6
            output_1Ddata[(i * BLOCK_COLS + j) * 10 + 4] = int(PAGE[i * 4 + 3][j * 3 + 1] > 1 ? 1 : 0) * 2 +
                int(PAGE[i * 4 + 2][j * 3 + 0] > 1 ? 1 : 0); // b5,b2
            output_1Ddata[(i * BLOCK_COLS + j) * 10 + 5] = int(PAGE[i * 4 + 2][j * 3 + 2]); // x1
            output_1Ddata[(i * BLOCK_COLS + j) * 10 + 6] = int(PAGE[i * 4 + 1][j * 3 + 1]); // x3
            output_1Ddata[(i * BLOCK_COLS + j) * 10 + 7] = int(PAGE[i * 4 + 0][j * 3 + 2]); // x4
            output_1Ddata[(i * BLOCK_COLS + j) * 10 + 8] = int(PAGE[i * 4 + 0][j * 3 + 0]); // x6
            output_1Ddata[(i * BLOCK_COLS + j) * 10 + 9] = int(PAGE[i * 4 + 0][j * 3 + 1] > 1 ? 1 : 0) * 2 +
                int(PAGE[i * 4 + 1][j * 3 + 2] > 1 ? 1 : 0); // y5,y2
        }
    }
}
