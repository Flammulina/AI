/************************************************************************
�T�ƎR�r�ƃL���x�c�ƒj (�[���D��T��)
************************************************************************/
#include<stdio.h>
#include<stdlib.h>

#define MAN     0
#define WOLF    1
#define GOAT    2
#define CABBAGE 3

#define SearchMax 20

int left_side[SearchMax][4];   /* ���݂̏�� */
int right_side[SearchMax][4];  /* �E�݂̏�� */

/************************************************************************
��Ԃ̕\��
���� state[i] : ���݂������͉E�݂̏��
 state[i]�̔z��̓��e�ɉ����ď�Ԃ�\������
(��) state[i]={1,1,1,1}�Ȃ�� [ �j �T �R�r �L���x�c ]
state[i]={1,0,1,0}�Ȃ�� [ �j �R�r ]
state[i]={0,0,0,0}�Ȃ�� [  ]
************************************************************************/
void print_state(int state[4])
{
	
	/*** ���̕����������ō쐬���� ***/
	//�e�v�f��1�Ȃ�Ε\��
	printf("[ ");
	if (state[0] == 1) {
		printf("�j ");
	}
	if (state[1] == 1) {
		printf("�T ");
	}
	if (state[2] == 1) {
		printf("�R�r ");
	}
	if (state[3] == 1) {
		printf("�L���x�c ");
	}
	printf("] ");
}

/************************************************************************
���ʂ̕\��
���� T : �X�e�b�v��
T�X�e�b�v�ڂ܂ł̌��ʂ�\������
�X�e�b�v��: [ ���݂̏�� ] [ �E�݂̏�� ]
(��) 0: [ �j �T �R�r �L���x�c ] [ ]
1: [ �T �R�r ] [ �j �L���x�c ]
************************************************************************/
void print_ans(int T)
{
	int t;
	/* ������Ԃ���T�X�e�b�v�ڂ܂ł̌��ʂ�\������
	[�q���g] print_state()�̊֐����������쐬����Ă����
	print_state(left_side[t]);  �� t�X�e�b�v�ڂ̍��݂̏�ԁA
	print_state(right_side[t]); �� t�X�e�b�v�ڂ̉E�݂̏��
	���\���ł��� */


	for (t = 0; t <= T; t++) {
		/*** ���̕����������ō쐬���� ***/
		printf("%d:",t);//t��\��
		print_state(left_side[t]);//���݂�\��
		print_state(right_side[t]);//�E�݂�\��
		printf("\n");//���s
	}
}

/************************************************************************
��Ԃ̃`�F�b�N
���� T                 : �X�e�b�v��
state[i]          : �`�F�b�N���������
past_state[t][i]  : �ߋ��̏��(t�X�e�b�v�ڂ̏��)
�E�T�ƎR�r�A�R�r�ƃL���x�c���c������Ԃł��Ȃ��A���ɒT�����ꂽ���
�ł��Ȃ���� 1��Ԃ�
�E����ȊO�� 0��Ԃ�
************************************************************************/
int check_state(int T, int state[4], int past_state[SearchMax][4]) {
	int i, t;
	int count;

	/* �T�ƎR�r �������� �R�r�ƃL���x�c���ꏏ�ɂȂ������`�F�b�N
	�����0��Ԃ� */
	
	/*** ���̕����������ō쐬���� ***/
	if ((state[1] && state[2])==1 || (state[2] && state[3])==1) {
		return 0;
	}


	/* �ߋ��ɓ�����Ԃ��Ȃ������`�F�b�N  �����0��Ԃ�
	[�q���g] past_state[t][i](t�X�e�b�v�ڂ̏��)��
	state[i](���݂̏��)���r���ă`�F�b�N */
	for (t = 0; t<T; t++) {
		count=0;//count�����Z�b�g
		/*** ���̕����������ō쐬���� ***/
		for (i = 0; i<4; i++) {
			//��v�����ꍇ��count�����Z
			if (past_state[t][i] == state[i]) {
				count++;
			}
		}
		if(count==4){//4���v�����Ȃ�0��Ԃ�
			return 0;
		}
		
	
	}
	/* ������ɂ��Y�����Ȃ����1��Ԃ� */
	return 1;
}

/************************************************************************
�[���D��T��
���� T                 : �X�e�b�v��
src_side[t][i]    : �j�����鑤�̏��
dest_side[t][i]   : �j�����Ȃ����̏��
************************************************************************/
void search(int T, int src_side[SearchMax][4], int dest_side[SearchMax][4]) {
	int i, j;

	int src_state[4];      /* �j�����鑤�̏�� */
	int dest_state[4];     /* �j�����Ȃ����̏�� */
	int new_src_state[4];  /* �j�����鑤�̎��̃X�e�b�v�̏�� */
	int new_dest_state[4]; /* �j�����Ȃ����̎��̃X�e�b�v�ł̏�� */

					/* T�X�e�b�v�ڂ̏�Ԃ��R�s�[ */
	for (i = 0; i<4; i++) {
		src_state[i] = src_side[T][i];
		dest_state[i] = dest_side[T][i];
	}

	for (i = 0; i<4; i++) { /* 0: �j 1: �T 2: �R�r 3: �L���x�c �����ɒ��ׂ� */
		if (src_state[i] == 1) { /* �ړ��ł���̂ł����(�j�Ɠ������ɂ���̂ł����) */
								 /* i�ƒj���ړ�(i��0�̏ꍇ�͒j�݈̂ړ�)������̏�Ԃ�
								 new_src_state[], new_dest_state[] �Ɋi�[
								 [�q���g] ���݂̏�� (src_state[], dest_state[])��
								 new_src_state[], new_dest_state[]�ɃR�s�[��,
								 i�ƒj���ړ������ꍇ�ɒl���ǂ̂悤�ɕω����邩��ݒ� */

								 /*** ���̕����������ō쐬���� ***/
			for(j=0;j<4;j++){
				new_src_state[j] = src_state[j];
				new_dest_state[j] = dest_state[j];
			}
			//�j��i�̏���Ί݂Ɉړ�
			new_src_state[0]=0;
			new_dest_state[0]=1;
			new_src_state[i]=0;
			new_dest_state[i]=1;

			/* i�ƒj���ړ�(i��0�̏ꍇ�͒j�݈̂ړ�)������̏�Ԃ��L�����ǂ�����
			�`�F�b�N���A�L���ł���� �݂̏�Ԃ��X�V���A���ɐi�� */
			if (check_state(T, new_src_state, src_side)) {
				/* �j�����݂ɂ���ꍇ(T�������̏ꍇ)
				left_side[T+1][]�� new_src_state[]���R�s�[
				right_side[T+1][]�� new_dest_state[]���R�s�[ */
				if (T % 2 == 0) {
					/*** ���̕����������ō쐬���� ***/
					for(j=0;j<4;j++){
					left_side[T + 1][j] = new_src_state[j];
					right_side[T + 1][j] = new_dest_state[j];
					}
				}
				/* �j���E�݂ɂ���ꍇ(T����̏ꍇ)
				right_side[T+1][]�� new_src_state[]���R�s�[
				left_side[T+1][]�� new_dest_state[]���R�s�[ */
				else {
					/*** ���̕����������ō쐬���� ***/
					for(j=0;j<4;j++){
					right_side[T + 1][j] = new_src_state[j];
					left_side[T + 1][j] = new_dest_state[j];
					}
				}
				/* �E�݂ɂ��ׂĂ��ړ����Ă���� ���ʂ�\�����ďI�� */
				//right_side[T+1][]���S��1�Ȃ��print_ans�ŏo��
				if (right_side[T+1][0]==1&&
					right_side[T+1][1]==1&&
					right_side[T+1][2]==1&&
					right_side[T+1][3]==1) {
					print_ans(T + 1);
					exit(0);
				}
				/* �����łȂ���΍ċA�I�ɒT���𑱂��� */
				else {
					search(T + 1, dest_side, src_side);
				}
			}
		}
	}
}

/************************************************************************
���C���v���O����
************************************************************************/
int main()
{
	int i, t;

	/* �z��̏����� (-1��ݒ�) */
	for (t = 0; t<SearchMax; t++) {
		for (i = 0; i<4; i++) {
			left_side[t][i] = -1;
			right_side[t][i] = -1;
		}
	}

	/*
	������Ԃ̐ݒ� */
	for (i = 0; i<4; i++) {
		left_side[0][i] = 1;
		right_side[0][i] = 0;
	}

	/* �T�� */
	search(0, left_side, right_side);

	return 0;
}



