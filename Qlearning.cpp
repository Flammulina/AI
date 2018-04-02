/************************************************************************
   Q�w�K
************************************************************************/
#include<stdio.h>
#include<stdlib.h>
#include<math.h>
// ���
#define START 0 // ���� (�X�^�[�g)
#define WOOD  1 // �X�@
#define LAKE  2 // ��
#define POND  3 // �r
#define FIELD 4 // ����
#define GOAL  5 // �� (�S�[��)

// �s��
#define EAST  0 // �� �@
#define WEST  1 // ��
#define SOUTH 2 // ��@
#define NORTH 4 // �k

#define TrialNo 50 // ���s��
#define StateNum 6  // ��Ԑ� 
#define ActNum 4    // �s����

#define Alpha 0.1 // �w�K�� �@�@
#define Gamma 0.9 // �������@�@

#define Reward 10 // ��V

/*******************************************************************
   �����̃V�[�h�̐���
********************************************************************/
void init_rnd()
{
  srand((unsigned int)time(NULL));//srand��time(NULL)�Ɏ��
}

/******************************************************************
  �����̔��� (0?1�̗���)
******************************************************************/
double Random()
{
  return((double)rand()/RAND_MAX);//rand()��RAND_MAX�Ŋ���A0~1�̗��������
}

/******************************************************************
  ���[���̉��l�̏�����
    Qvalue[s][a] : ���s�ɂ����čs��a����邱�Ƃ̉��l
******************************************************************/
void init_Q(double Qvalue[StateNum][ActNum])
{
  int s,a;

  /* ���ׂĂ̏�Ԃƍs���̉��l��0�ɂ��� */
  /*** ���̕����������ŏ��� ***/
  for(s=0;s<StateNum;s++){
  	for(a=0;a<ActNum;a++){
		Qvalue[s][a]=0;
  	}
  }

}

/******************************************************************
  �s���̑I�� (�{���c�}���I��)
    state        : ���
    Qvalue[s][a] : ���s�ɂ����čs��a����邱�Ƃ̉��l�@�@
    env[s][a]    : ���s�ɂ����čs��a��������Ƃ��ɑJ�ڂ�����
    t            : ���s��
******************************************************************/
int select_action(int state,
		  double Qvalue[StateNum][ActNum], 
		  int env[StateNum-1][ActNum],int t)
{
  double sum;    // ���[���̉��l�̍��v
  int a;         // �s��    
  double r;      // ���� (0�`sum�̊Ԃ̗���)
  double border; // ���E��
  double T=10;   // ���x�p�����[�^

  /* ���x�p�����[�^��ݒ� */
  //���x�p�����[�^���牼����t������1�ȉ��Ȃ�1�ɒ�߂�
  T=T-t;
  if(T<=1) T=1;

  /* ���[���̉��l�̍��v���v�Z �@�@
     ���̏�ԂŎ��Ȃ��s��(env[state][a]=-1)
     �̉��l�͍��v�ɂ͊܂܂Ȃ� */
  /*** ���̕����������ŏ��� ***/
  //sum��0��
  sum=0;
  for(a=0;a<ActNum;a++){
   /* ��邱�Ƃ̂ł���s���̒�����s����I�� */
       if(env[state][a]!=-1){
      sum += exp(Qvalue[state][a]/T);
   }
  }
  
  
  /* 0�`sum�̗����𐶐� */
  r = Random()*sum;
  border=0;
  for(a=0;a<ActNum;a++){
    /* ��邱�Ƃ̂ł���s���̒�����s����I�� */
    if(env[state][a]!=-1){
      border += exp(Qvalue[state][a]/T);
    }
    /* �I�����ꂽ�s����Ԃ� */
    if(r<=border){
      return a;
    }
  }
}

/******************************************************************
  ���[���̉��l�̍X�V
    Qvalue[s][a] : ���s�ɂ����čs��a����邱�Ƃ̉��l
�@�@p_state      : ���O�̏��
    act          : �s��
�@�@state        : ��� (�s����̏��)�@ �@�@
    r            : ��V
******************************************************************/
void update_Q(double Qvalue[StateNum][ActNum], 
	      int p_state, int act, int state, int r)
{
  int a;
  double max; // �s����̏�Ԃ����邱�Ƃ̂ł���s���̒��ł̉��l�̍ő�l�@

  /* ��邱�Ƃ̂ł���s���Ɋւ��鉿�l�̒��ōő�l�����߂� */ 
  /*** ���̕����������ŏ��� ***/
  //max��0��
  max=0;
  //for�����ŁAQvalue[state][a]��max�����傫����΁Amax���X�V
  for(a=0;a<ActNum;a++){
    if(max<=Qvalue[state][a]){
	  max=Qvalue[state][a];
    }
  }
  /* ���p_state�ɂ����čs��act���Ƃ邱�Ƃ̉��l���X�V */
  /*** ���̕����������ŏ��� ***/
 Qvalue[p_state][act]=Qvalue[p_state][act]+Alpha*(r+Gamma*max-Qvalue[p_state][act]);
}
/************************************************************************
  ���C���v���O����
************************************************************************/
int main()
{
  int t;
  int s,a;
  int act;     // �s�� �@
  int p_state; // ���O�̏�ԁ@
  int state;   // ���
  double Qvalue[StateNum][ActNum]; //�@���[���̉��l
  // �� (��Ԃ̑J��) �@�@�@�@�@��  �@��  �@��@  �k
  int env[StateNum-1][ActNum]={{WOOD, -1,    POND, -1},    // �����@�@�@�@
			       {LAKE, START, FIELD,-1},    // �X�@
			       {-1,   WOOD,  GOAL, -1},    // �΁@
			       {FIELD,-1,    -1,   START}, // �r
			       {-1    ,POND, -1,   WOOD}}; // �����@
  int count; // �G�s�\�[�h�̒����@
  char *states[StateNum]={"����","�X","��","�r","����","��"}; // ���(�\���p)�@
  char *acts[ActNum]={"��","��","��","�k"};  // �s��(�\���p)
  FILE *fp; // �t�@�C���|�C���^ 

  /* ���ʕۑ��p�̃t�@�C��(result.dat)���I�[�v�� */
  if((fp=fopen("result.dat","w"))==NULL){
    printf("main() : Cannot open \"result.dat\"\n");
    exit(1);
  }

  init_rnd();      /* �����̏����� */
  init_Q(Qvalue);  /* ���[���̉��l�̏����� */

  /* TrialNo��̎��s���J��Ԃ� */
  for(t=0;t<TrialNo;t++){
    printf("[%d]",t);
    state = START; /* ��Ԃ�������(START�ɐݒ�) */
    count=0; /* �G�s�\�[�h�̒�����0�ŏ����� */
    /* �S�[���ɓ��B����܂ŌJ��Ԃ� */
    while(state!=GOAL){
      act=select_action(state,Qvalue,env,t); /* �s����I�� */
      p_state=state; /*�@��Ԃ�ۑ� */
      state=env[p_state][act]; /* �s�����邱�Ƃɂ���Ԃ��J�� */
      /* �S�[���ɓ��B�������V���擾���A���[���̉��l���X�V */
      if(state==GOAL){
	update_Q(Qvalue,p_state,act,state,Reward);
      }
      /* ���[���̉��l���X�V(�S�[���ȊO�ł͕�V��0) */
      else{
	update_Q(Qvalue,p_state,act,state,0);//��V0��update_Q
      }    
      /* ��Ԃƍs������ʂɕ\�� */
      printf("%s==>(%s)==>",states[p_state],acts[act]);
      /* �G�s�\�[�h�̒�����1���₷ */
      count++;
    }
	//�����܂Ń��[�v
	
    /* �ŏI�I�ȏ�Ԃ���ʂɕ\�� */
    printf("%s\n",states[state]);
    /* ���s�񐔂ƃG�s�\�[�h�̒������t�@�C���ɏo�� */
    fprintf(fp,"%d %d\n",t,count);
  }
  /* �t�@�C�����N���[�Y */
  fclose(fp);

  /* �ŏI�I�ȃ��[���̉��l�ۑ��p�̃t�@�C�����I�[�v�� */ 
  if((fp=fopen("Q.dat","w"))==NULL){
    printf("main() : Cannot open \"Q.dat\"\n");
    exit(1);
  }

  /* ���[���̉��l���t�@�C���ɏ����o�� */
  fprintf(fp," �@�@�@�@�@���@ �@���@�@�@��@�@�@�k\n");
  for(s=0;s<StateNum;s++){
    fprintf(fp,"%s\t",states[s]);
    for(a=0;a<ActNum;a++){
      fprintf(fp,"%6.3lf\t",Qvalue[s][a]);
    }
    fprintf(fp,"\n");
  }

  /* �t�@�C�����N���[�Y  */
  fclose(fp);
}



