#include <stdio.h>

void extract(
    unsigned int extract_size,
    unsigned char * read_data,
    int read_data_len,
    unsigned int * extracted_data,
    unsigned int numRows)
{
    unsigned char mask = (1<<extract_size)-1;

    //calculate the initial offset of the data
    int bits_to_ignore = (read_data_len* 8)-(numRows*extract_size);
    printf("%d\n", bits_to_ignore);

    int data_index = 0;
    int offset = (8-extract_size)-bits_to_ignore;
    for(int i=0; i < numRows; i++){
        if(offset < 0){
            offset = (8-extract_size);
            data_index++;
        }
        extracted_data[i] = (read_data[data_index] >> offset) & mask;
        //printf("Row %d | Data %d | Offset %d\n", i, data_index, offset);
        offset-=extract_size;
    }
}

void encode(
    unsigned int paramSize,
    unsigned char* data_send,
    int sendData_len,
    unsigned int * rows_from,
    unsigned int numRows)
{
    //init the data_send to 0
    for(int i=0; i < sendData_len; i++){
        data_send[i] = 0;
    }

    //fill the rows w the data
    unsigned int dataIndex=0;
    int offset = (8-(((sendData_len*8)-(2*numRows))))-2;
    for(int i=0; i < numRows; i++){
        data_send[dataIndex] = (rows_from[i] << offset) | data_send[dataIndex];
        //printf("Row %d | Data %d | Offset %d\n", i, dataIndex, offset);

        //move to the next buffer location
        offset -= paramSize;
        if(offset < 0){
            offset=8-paramSize;
            
            //increase the data index
            dataIndex+=1;
        }
    }
}

int main(){
    unsigned char read_data[3] = {0x04,0x51,0x15};
    unsigned int ext_data[10];
    unsigned char decoded_data[3];

    extract(2,&read_data[0],3,&ext_data[0],10);

    //print ext_data
    printf("Extracted Data\n");
    for(int i=0; i < 10; i++){
        printf("%u\n",ext_data[i]);
    }

    printf("\nCompacted Data\n");
    encode(2,&decoded_data[0],3,&ext_data[0],10);

    for(int i=0; i < 3; i++){
        printf("%u\n",decoded_data[i]);
    }

    return 0;
}