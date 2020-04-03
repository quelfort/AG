#include <math.h>
#include <cstdlib>
#include <iostream>
#include <stdio.h>

struct individuo{
	int *binario;//vetor com apenas numeros binários
	double natural;//Serve para representar cada individuo como uma digital
	double objetivo;//Serve para guardar o valor da função objetivo
    bool restricao;//Serve para saber se as restrições foram satisfeitas
    double aptidao;//Valor da função objetivo com a aplicação das penalidades
};

struct variavel{
	int tamanho;//guarda o tamanho de bits necessarios da variável
	int precisao;//guarda a precisão desejada para essa variável
	double inferior;//Guarda o limite inferior da variável
	double superior;//Guarda o limite superior da variável
};
//fim

struct grafico{
       float apt;
       };

using namespace std;


void exibir(individuo pop[],int itamanho,int ptamanho){
	cout << endl << "Os  melhores individuos sao: " << endl << endl;

     for(int i=0;i<5;i++)
     {

            for(int j=0;j<itamanho;j++)
            {
			cout << pop[i].binario[j] ;
			}

            cout << "\t" << pop[i].aptidao << endl;
     }



	cout << endl;

}


float AvaliaIndividuoAlveolar (float dminx, float dminy, float lx, float ly, float hmax,float bmax, float q, float gpr, float gpl, float cap, float cad, int ptamanho, int nxmax, int nymax, int nvv, int numgen, int k, int numpav,individuo pop[] )
{

// F                = Função aptidão
// Custo total      = Função objetivo (sem as restrições)
// k                = indica os indivíduos a serem avaliados

//Contadores inteiros

//------------------------------------------------------------------------------------------------------------

   int i,j,p;
   int apop[ptamanho][numgen];
   //ptamanho neste caso  e numgen é o numero de cromossomos


            for (j=0; j<numgen; j++)
            {
                apop[k][j]=pop[k].binario[j];

            }


    float ccml[4];
    float cpm[4];


//------------------------------------------------------------------------------------------------------------



    //CUSTO CONCRETO CML


	ccml[0]=147;
	ccml[1]=158;
	ccml[2]=171;
	ccml[3]=185;

//------------------------------------------------------------------------------------------------------------


     //CUSTO CONCRETO CPM

   cpm[0]=185;
   cpm[1]=200;
   cpm[2]=216;
   cpm[3]=233;

//------------------------------------------------------------------------------------------------------------
/*	             Definição Variáveis lOCAIS

	               Variáveis de Projeto

	         Variáveis da configuração estrutural
*/
//------------------------------------------------------------------------------------------------------------

	int nx,ny;     // Número de vãos na direção X e Y	- VP
	int dl;        // Direção da laje: 1 (direção Y) e 0 (direção X) - VP
	float ajx,ajy;

//------------------------------------------------------------------------------------------------------------

//	             Variáveis Auxiliares

	float llj,llv,rpilar;    // Vão da laje e vão da viga E REACAO NO PILAR
	float lp,sp;  		     //LP= Lado pilar SP=SEÇÃO DO PILAR
	float ro;			     // TAXA AÇO PILAR
	float lljc;             // Vão da laje corrigido (descontado BV)

//------------------------------------------------------------------------------------------------------------

//	            Variáveis do material



	int fckml[4];                 // Fck moldado in loco
    int fckpm[4];                 // Fck pré-moldado
	int	pm,cml;                //Contadores dos fcks - VP

//------------------------------------------------------------------------------------------------------------

//	          Variáveis Quantidade Peças

	int  qdp;
	int  qdl, qdv;  // Qdes de viga, laje e pilar

//------------------------------------------------------------------------------------------------------------


//            Variáveis dos custos


	float dop, cdop;                          // Despesas operacionais lajes
	float ctv, ctl, ctp, ctt;                 // CUSTOS TRANSPORTE
	float ctmv, ctml, ctmp, ctmt,custoneo;    // CUSTOS MONTAGEM

//------------------------------------------------------------------------------------------------------------


//	                 Variáveis da Laje
//	             Variáveis de Projeto: VL

	int vl;                          // Caracteriza a laje
	float hl[32], pa[32],apl[32];    // Força Protensão antes transferência (MN)
							         // Área de Protensão na Laje (m2)
//------------------------------------------------------------------------------------------------------------


//	             Variáveis Auxiliares

	float m,ac,ygc;                                 // relação fcks, área capa corrigida, cg sç composta
	float ic;                                       // Momento inércia sç composta
	float yg[64],a[64],ii[64],xmax[64];             // dados seção isolada
	float ep,epc,winf,wsup,wcinf,wcsup;             // excentricidades e módulos LAJES
	float carga[6],ml[6],rl[6];                     // Auxiliares cálculo esforços
	float mld,vld;                                  // Momento e cortante de cálculo (faixa de 1.2m)
	float tinf,tsup,tcinf,tcsup;                    // Tensões na LAJE
	float scp,spt,pt,pinf;                          // Auxiliares na protensão
	float tinpt,tsupt,tinpi,tsupi;	                // Tensões protensão
	float tdesi,tdess,tti,tts,ttii,ttss,tmi,tms;    // tensões atuantes transitórias
	float des,ff,lcj,ltj,lck,ltk;                   // tensões limites
	float xtl,xl,zl,zla,zlb,mresl;                  // auxiliares elu
	float bxl, ddl, penl;                           // beta x da laje, altura útil laje e penalidade laje
	float cfi, cft, fi, ft, eil;                    // Contra-flecha e flecha das lajes

//------------------------------------------------------------------------------------------------------------

//	                Variáveis da Viga
//	              variáveis de projeto: vv

	int vv;
	float hv[32],bv[32];                  // geometria da viga
	float ht;                             // altura total do pavimento
	int nmax[32];  	                      // qde máx. de cordoalha por camada
	int ana,anb,nbaux;                    // qde de cordoalhas por camada
	int na[16];
    int nb[16];
	int npt[4];                           // qde de barras passivas de tração
 	float bp[4];                          // bitolas passivas


//------------------------------------------------------------------------------------------------------------

//	               variáveis auxiliares (geometria e tensões)

	float av,ppv,me,ygv,iv;                    // área, peso próprio, mom. estático,cg, m. inércia
	float avc,ppvc,mec,ygcv,ivc;               // dados sç composta
	float epa,epb,epcv;                        // excentricidade sç isolada
	float epca,epcb,epccv;                     // excentricidade sç composta
	float da,db,apa,apb,as;                    // altura útil e área de armaduras
	float wvi,wvs,wcvi,wcvs;                   // módulos resistentes
	float mvt,mvpp,mvg,mvq,mvd;                // momentos
	float tvi,tvs,tvppi,tvpps,tvgi,tvq;        // tensões
	float bxv,penv;                            // beta x viga e penalidade viga
	int anpt,abp;						       // auxiliares contador

//------------------------------------------------------------------------------------------------------------

//				 Variáveis auxiliares (protensão)

	float pav,soma,soma2,sptv,pat,soma3,pats,protsup;
	float vtinpt,vtsupt,vpinf,vtinpi,vtsupi;
	float ltjv,ltkv,descompv,ffissv;
	float tdiv,tdsv,ttiv,ttsv,ttiiv,ttssv,tmiv,tmsv;

//------------------------------------------------------------------------------------------------------------
//		     	variáveis auxiliars (elu) / (els)

	float xv,za,zb,mresv;
	float cfiv,cftv, fiv, ftv;


//------------------------------------------------------------------------------------------------------------

//			   variáveis das restrições

	float gl[17];  //restrições lajes
	float gv[20];  //restrições vigas

//------------------------------------------------------------------------------------------------------------


//		     	Variáveis aptidão / custos

	float  vpmv,vpml,vpmp,vml,vapv,vapl,vadv;                            // volume dos materiais
	float  custoconc, custoconcml,custoprot,custoad,custotal, custofab;  // custos material
	float  custocis,custope,custolig;
	float  pentotal;                                                     // somatório penalidades
	float  lpl,nlp,qdpl,ptal,lpv,nvp,qdpv,ptav;

//------------------------------------------------------------------------------------------------------------

//                  BANCO DE DADOS

//		Listas das Variáveis dos Materiais
//            Resitências Materiais (fcks)




	for(i=0;i<4;i++)
    {

	fckpm[i]=35+(i)*5;	 //!  35,40,45,50 (valores fckpm)

	fckml[i]=20+(i)*5;	 //!  20,25,30,35	(valores fckml)
	}

/*------------------------------------------------------------------------------------------------------------
  			        LISTAS LAJES

       	  Vinculação da variável VL das Lajes
	       Propriedades geométricas das Lajes
			    Painéis de b=1,20 m

	 Definição propriedades da laje seção PM - T&A
				   Banco Dados - Laje*/

	for(i=0;i<4;i++)
    {
	hl[i]=0.09;	            // altura da laje(m)
	a[i]=0.0669983;	        //área da laje (m2)
	yg[i]=0.045;		    // cg da laje (m)
	ii[i]=0.000063;		    // momento de inércia da laje (m4)
	xmax[i]=0.065;          // máximo x (ln)
	}

	for(i=4;i<9;i++)
    {
	hl[i]=0.13;
	a[i]=0.0918954;
	yg[i]=0.06784;
	ii[i]=0.00018;
	xmax[i]=0.07;           // máximo valor do x (compressão)
	}

	for(i=9;i<15;i++)
    {

	hl[i]=0.17;
	a[i]=0.1136454;
	yg[i]=0.08847;
	ii[i]=0.000396;
	xmax[i]=0.075;
	}

	for(i=15;i<21;i++)
    {

	hl[i]=0.2;
	a[i]=0.1267849;
	yg[i]=0.1;
	ii[i]=0.00063;
	xmax[i]=0.0725;
	}

	for(i=21;i<27;i++)
    {

	hl[i]=0.21;
	a[i]=0.135401;
	yg[i]=0.108;
	ii[i]=0.000734;
	xmax[i]=0.08;
    }


	for(i=27;i<32;i++)
    {

	hl[i]=0.26;
	a[i]=0.1816019;
	yg[i]=0.129;
	ii[i]=0.00144;
	xmax[i]=0.085;
	}

/*------------------------------------------------------------------------------------------------------------
                	força de protensão (mn) - lajes

                       pa=n.acor.1453.0,97.(10-6)

                        sinal (-) / compressão*/

      pa[0]=-0.184350828;
      pa[1]=-0.245801104;
      pa[2]=-0.30725138;
      pa[3]=-0.368701656;
      pa[4]=-0.245801104;
      pa[5]=-0.341640984;
      pa[6]=-0.431843224;
      pa[7]=-0.52430052;
      pa[8]=-0.62577804;
      pa[9]=-0.245801104;
      pa[10]=-0.341640984;
      pa[11]=-0.431843224;
      pa[12]=-0.52430052;
      pa[13]=-0.62577804;
      pa[14]=-0.74980612;
      pa[15]=-0.431843;
      pa[16]=-0.524301;
      pa[17]=-0.625778;
      pa[18]=-0.749806;
      pa[19]=-1.143313;
      pa[20]=-1.429142;
      pa[21]=-0.431843;
      pa[22]=-0.524301;
      pa[23]=-0.625778;
      pa[24]=-0.749806;
      pa[25]=-1.143313;
      pa[26]=-1.429142;
      pa[27]=-0.431843;
      pa[28]=-0.524301;
      pa[29]=-0.625778;
      pa[30]=-0.749806;
      pa[31]=-1.143313;



//	           área de protensão total no painel da laje


      apl[0]=0.0001308;
      apl[1]=0.0001744;
      apl[2]=0.000218;
      apl[3]=0.0002616;
      apl[4]=0.0001744;
	  apl[5]=0.000242;
      apl[6]=0.0003064;
      apl[7]=0.000372;
      apl[8]=0.000444;
      apl[9]=0.0001744;
      apl[10]=0.0002424;
      apl[11]=0.0003064;
      apl[12]=0.000372;
      apl[13]=0.000444;
      apl[14]=0.000532;
      apl[15]=0.000306;
      apl[16]=0.000372;
      apl[17]=0.000444;
      apl[18]=0.000532;
      apl[19]=0.000811;
      apl[20]=0.001014;
      apl[21]=0.000306;
      apl[22]=0.000372;
      apl[23]=0.000444;
      apl[24]=0.000532;
      apl[25]=0.000811;
      apl[26]=0.001014;
      apl[27]=0.000306;
      apl[28]=0.000372;
      apl[29]=0.000444;
      apl[30]=0.000532;
      apl[31]=0.000811;

//------------------------------------------------------------------------------------------------------------

//      	    listas das variáveis vigas
//      	 qde de barras passivas de tração

      npt[0]=0;
      npt[1]=2;
      npt[2]=4;
      npt[3]=6;

//	    área das bitolas passivas disponíveis

     	bp[0]=0.000028;   // 6.0mm
    	bp[1]=0.000050;	  // 8.0mm
    	bp[2]=0.000080;   // 10.0mm
    	bp[3]=0.000125;   // 12.5mm

//       qde de cabos camada "a"

	   na[0]=3;
       na[1]=5;
       na[2]=6;
       na[3]=7;
	   na[4]=8;
       na[5]=10;
       na[6]=13;
       na[7]=14;
	   na[8]=15;
       na[9]=16;
       na[10]=17;
       na[11]=18;
	   na[12]=19;
       na[13]=20;
       na[14]=21;
       na[15]=23;

//      qde de cabos camada "b"

	  nb[0]=3;
      nb[1]=5;
      nb[2]=6;
      nb[3]=7;
      nb[4]=8;
      nb[5]=10;
      nb[6]=13;
      nb[7]=14;
	  nb[8]=15;
      nb[9]=16;
      nb[10]=17;
      nb[11]=18;
	  nb[12]=19;
      nb[13]=20;
      nb[14]=21;
      nb[15]=23;

//------------------------------------------------------------------------------------------------------------

//		características geométricas da viga


      for(i=0; i<5; i++){
     	hv[i]=0.20+(i)*0.05;   // altura
     	hv[i+5]=hv[i];
    	hv[i+10]=hv[i];
     	hv[i+15]=hv[i];
    	hv[i+20]=hv[i];
		hv[i+25]=hv[i];

    	bv[i]=0.40;	           // base
    	bv[i+5]=0.50;
    	bv[i+10]=0.60;
    	bv[i+15]=0.70;
    	bv[i+20]=0.80;
		bv[i+25]=0.90;

    	nmax[i]=13;	            // qde máxima de cordoalhas por base de viga
    	nmax[i+5]=15;
    	nmax[i+10]=17;
    	nmax[i+15]=19;
    	nmax[i+20]=21;
		nmax[i+25]=23;
	  }

//   complemento	das listas das vigas (32 possíveis)

		hv[30]=hv[28];
        bv[30]=bv[28];
        nmax[30]=nmax[28];
		hv[31]=hv[29] ; //
        bv[31]=bv[29];
        nmax[31]=nmax[29];

//------------------------------------------------------------------------------------------------------------


//
//	               ROTINA PARA DECODIFICAÇÃO
//
//	  Com: As variáveis que começam com "A" são auxiliares
//
//	  Com: Este "K" vem do Loop no programa principal (k=1 até numind)
//


	dl=apop[k][0];                                     // já é o próprio valor

	pm=2*apop[k][1]+1*apop[k][2];   // auxiliar

//	cout<<fckpm[pm]<<endl;

	cml=2*apop[k][3]+1*apop[k][4];   // auxiliar

	//cout<<fckml[cml]<<endl;

	vl=16*apop[k][5]+8*apop[k][6]+4*apop[k][7]+2*apop[k][8]+1*apop[k][9];	 // auxiliar


	anpt=2*apop[k][10]+1*apop[k][11] ;        // auxiliar lista npt

	abp=2*apop[k][12]+1*apop[k][13];                      // auxiliar p a lista bp

	ana=8*apop[k][14]+4*apop[k][15]+2*apop[k][16]+1*apop[k][17];	 // auxiliar

	anb=8*apop[k][18]+4*apop[k][19]+2*apop[k][20]+1*apop[k][21];				 // auxiliar

	nx=0;

	for(i=1; i<(1+nxmax); i++)
    {

	nx=int(nx+apop[k][21+i]*pow(2,(nxmax-i)));

	}

	nx=nx+1;

	ny=0;

	for(i=1; i<(nymax+1); i++)
    {
             // a função int arredonda pra baixo mas há o nx+1;

	ny=int(ny+apop[k][21+nxmax+i]*pow(2,(nymax-i)));

	}

	ny=ny+1;


	vv=0;

	for(i=1; i<(nvv+1); i++)
    {


	vv=int(vv+apop[k][21+nxmax+nymax+i]*pow(2,(nvv-i)));

	}


/*------------------------------------------------------------------------------------------------------------

!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
!
!                     REDUÇÃO DO DOMÍNIO DA BASE
!
!                   TÉCNICA: ALTERAR O VALOR DE VV
!
!	EXISTE UM ESPAÇO INFACTÍVEL MAS FAZ-SE TRANSFORMACAO NA LISTA
!
!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
*/

	if (bmax==0.40)
    {
					  if (vv>5) {
					               if (vv<11)
			                       vv=vv-5;
						           else
                                   vv=vv-10;

					             }
	}


	if (bmax==0.50)  {
	                   if (vv>10)  {
					                  vv=vv-5;
					                }
  	}

	if (bmax==0.60)
    {
	                   if (vv==16)  {
					                  vv=15;
                                      }

	}

	if (bmax==0.70)
    {
					  if (vv>20)
                      {
					               if (vv<26)
                                   vv=vv-5;
						           else
			                       vv=vv-10;

					  }
}

	if (bmax==0.80)
    {
	                   if (vv>25)
	                   {
					                  vv=vv-5;
					   }
	}

//------------------------------------------------------------------------------------------------------------

/*!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
!
!			  AJUSTE DO NA P NAO ULTRAPASSAR O NMAX
!
!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!*/

	if (na[ana]>nmax[vv]){
	                           na[ana]=nmax[vv];
                         }


	if (nb[anb]>nmax[vv])
                        {
	                           nb[anb]=nmax[vv];
                         }


//------------------------------------------------------------------------------------------------------------
/*!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
!																		   !
!							TRANSGÊNICO (NA x NB)
!
!	           Troca por um fenótipo que melhor se adapte ao problema
!																		   !
!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!*/



ajx=lx/dminx;

 if (nx>ajx)   {
                  nx=nx*100;
                  }

 ajy=ly/dminy;

 if (ny>ajy)   {
                  ny=ny*100;
                  }


//       cálculo dos vãos

	llj=(lx/nx)*(1-dl)+(ly/ny)*(dl);		 // (m)
	llv=(lx/nx)*(dl)+(ly/ny)*(1-dl);		 // (m)



	lljc=llj-bv[vv];      // vão laje corrigido (m)


/*------------------------------------------------------------------------------------------------------------
!					LAJES ALVEOLARES
!
!		            Rotina de Cálculo
!
!	  Comentário: A tração tem sinal + e a compressão -
!
!          Definição propriedades seção composta da Laje
!		   Painel de b=1,2 m
*------------------------------------------------------------------------------------------------------------*/



	m=pow((float(fckml[cml])/float(fckpm[pm])),0.5);
	ac=m*1.2*0.05;
 	ygc=((a[vl]*yg[vl])+(ac*(hl[vl]+0.025)))/(a[vl]+ac);

    ic=ii[vl]+a[vl]*pow((ygc-yg[vl]),2)+(m*1.2*(pow(0.05,3))/12)+ac*pow((hl[vl]+0.025-ygc),2);

//------------------------------------------------------------------------------------------------------------
//		 excentricidades e módulos resistentes das lajes

	ep=yg[vl]-0.012-0.006;	// (m) seção isolada, adotado cl=1,2cm
	epc=ygc-0.012-0.006;	    // (m) seção composta

	winf=ii[vl]/yg[vl];
	wsup=ii[vl]/(yg[vl]-hl[vl]);
 	wcinf=ic/ygc;
	wcsup=ic/(ygc-hl[vl]-0.05);

//------------------------------------------------------------------------------------------------------------
//       Cálculo dos momentos e tensões nas Lajes
//	        Com: Cálculo por painel (b=1.2m)
//

	carga[0]=a[vl]*2.5;	      // peso próprio laje (tf/m)
	carga[1]=0.125*1.2;       // peso capa (tf/m)
	carga[2]=gpr*1.2;	      // pav+rev	  (tf/m)
	carga[3]=gpl*1.2;	      // paredes sobre laje (tf/m)
	carga[4]=q*1.2;		      // carga acidental	(tf/m)
	carga[5]=0.05*1.2;        // carga de trabalho sobre a laje (tf/m) (50kg/m2)

	for (i=0; i<6 ; i++)
	{

	ml[i]=carga[i]*pow(lljc,2)/8;	 // momento em tf.m/(b=1.2m)
	rl[i]=carga[i]*(llj)/2  ;     // reação/cortante (tf) por painel (b=1.2m)
	}

//	   Ações de Cálculo por painel (MN.m e MN)

	mld=(1.3*ml[0]+1.4*(ml[1]+ml[2]+ml[3]+ml[4]))/100; // mom. de cálculo  laje
	vld=(1.3*rl[0]+1.4*(rl[1]+rl[2]+rl[3]+rl[4]))/100; // cortante de cálc. laje


//         Tensões Fase de concretagem (peça isolada)
//
//		   Tf/100=MN

	tinf=((ml[0]+ml[1]+ml[5])/winf)/100;   // (mpa)
	tsup=((ml[0]+ml[1]+ml[5])/wsup)/100;	  // (mpa)

//		Tensões após concretagem (seção composta)

	tcinf=((ml[2]+ml[3]+ml[4])/wcinf)/100;	// (mpa)
	tcsup=((ml[2]+ml[3]+ml[4])/wcsup)/100;	// (mpa)

//	  força de protensão

//	  protensão inicial - ato da transferência (pa)
//
//	pa=nc*acor*1453*0.97   // força de protensão inicial (mn)
//
//	  nc*acor=pa/0.001409


//	  protensão após transferência (pt)

	scp=(pa[vl]/a[vl])+pa[vl]*(pow(ep,2)/ii[vl]); // mpa (sinal -)

	spt=(-1)*((pa[vl]/a[vl])+pa[vl]*(ep/winf))+(195000/(0.85*5600*(pow(fckpm[pm],0.5))))*scp;	 // (sinal -)

	pt=pa[vl]-apl[vl]*spt;	// mn

//	  restrição - término da protensão



//	  protensão tempo infinito (pinf)

	pinf=0.75*pa[vl];		 // perda estimada (75% da força inicial)

//	  tensões devido à protensão

	tinpt=(pt/a[vl])+pt*(ep/winf);	  // tensões na seção pm após
	tsupt=(pt/a[vl])+pt*(ep/wsup);	  // transferência da protensão

	tinpi=(pinf/a[vl])+pinf*(ep/winf);  // tensõe na seção pm num tempo infinito
	tsupi=(pinf/a[vl])+pinf*(ep/wsup);

//        restrições - verificações em vazio

//         tensões atuantes em vazio (mpa)

  	tdesi=tinpt+(ml[0]/winf)/100;     // desmoldagem inferior
	tdess=tsupt+(ml[0]/wsup)/100;     // desmoldagem superior
	tti=tinpt+0.8*(ml[0]/winf)/100;   // transporte inferior (0.8)
	tts=tsupt+0.8*(ml[0]/wsup)/100;   // transporte superior (0.8)
	ttii=tinpt+1.3*(ml[0]/winf)/100;  // transporte inferior (1.3)
	ttss=tsupt+1.3*(ml[0]/wsup)/100; // transporte superior (1.3)
	tmi=tinpt+tinf;                   // montagem inferior
	tms=tsupt+tsup; 		             // montagem superior

//	  tensões els  (mpa)
//	 descompressão

	des=((ml[0]+ml[1])/winf)/100+tinpi+((ml[2]+ml[3])/wcinf)/100+0.3*(ml[4]/wcinf)/100;

//	 formação de fissura (mpa)

	ff=((ml[0]+ml[1])/winf)/100+tinpi+((ml[2]+ml[3])/wcinf)/100+0.4*(ml[4]/wcinf)/100;

//		tensões limites

	lcj=0.49*fckpm[pm];                 // limite compressão fckj (transitória)
	ltj=1.2*0.7*0.3*pow((0.7*fckpm[pm]),(2/3)); // limite tração fckj

	lck=0.7*fckpm[pm];                // limite compressão fck   (els)
	ltk=1.2*0.7*0.3*pow((fckpm[pm]),(2/3)); // limite tração fck / seção "t" (els)

//
//		 solicitações normais - elu	(lajes alveolares)
//
//	 obs: será testada a roti na que não necessita do cálculo do pré
//		  alongamento
//

	ddl=(hl[vl]+0.03875);  // altura útil da laje simplificada

	xtl=2551.05*apl[vl]/fckml[cml]; // para o painel b=1.2m

	if (xtl<=0.05)
    {

	xl=xtl;
	zl=ddl-0.4*xl;
	mresl=apl[vl]*1486.9*zl;
    }

	else{

	xl=((1486.9*apl[vl]-0.0291*fckml[cml])/(0.58285*fckpm[pm]))+0.05;
	zla=ddl-0.4*xl;
	zlb=ddl-0.02;
	mresl=(0.0291*fckml[cml]*zlb)+(0.58285*fckpm[pm]*(xl-0.05)*zla);
    }



/////////////////////////////////////////////////////////////////////////////
//																		  //
//                     ROTINA FLECHAS EM LAJES							  //
//																		  //
/////////////////////////////////////////////////////////////////////////////
//                     CONTRA-FLECHA (PROTENSÃO)

	cfi=(pa[vl]*ep*lljc)/(8*4760*pow(fckpm[pm],0.5)*ii[vl]); // contra-flecha inicial

	cft=cfi*2.2;   // estimativa contra-flecha total (sinal"-")


//                         FLECHA  (CARREGAMENTO)

	fi=3*(carga[0]+carga[1]+carga[2]+carga[3]+0.3*carga[4])*pow(lljc,4)/100;

	eil=(384*4760*pow(fckpm[pm],0.5)*ic);   // flecha inicial (sç composta)



	ft=(fi/eil)*2.5;   // estimativa flecha total (sinal "+")
					  // total=2.5*inicial


//
//		RESTRIÇÕES
//
//	  Restrições estado vazio - Inferior (comprimida)
// 		Em módulo p compensar o sinal (-) compressão
//
// Obs: Alguns valores referências são multiplicados p aumentar a margem
//

	if (fabs(tdesi)<=lcj)
	                       gl[0]=0;
	                       else
						   gl[0]=fabs(tdesi/lcj)-1;

	if (fabs(tti)<=lcj)
		                     gl[1]=0;
	                         else
							 gl[1]=fabs(tti/lcj)-1;


	if (fabs(ttii)<=lcj)
	                      gl[2]=0;
	                      else
						  gl[2]=fabs(ttii/lcj)-1;

	if (fabs(tmi)<=lcj)
	                     gl[3]=0;
	                     else
						 gl[3]=fabs(tmi/lcj)-1;

//	  restrições em vazio - superior (tracionada)
//		  não precisa ser em módulo

	if (tdess<=(2*ltj))
	                  gl[4]=0;
	                  else
					  gl[4]=fabs(tdess/(2*ltj))-1;


//	if (tts.le.(2*ltj)) then
    if (tts<=pow((0.7*fckpm[pm]),0.5))  // limite aci

	                gl[5]=0;
	                else
					gl[5]=fabs(tts/pow((0.7*fckpm[pm]),0.5))-1;


	if (ttss<=(2*ltj))
	                 gl[6]=0;
	                 else
					 gl[6]=fabs(ttss/(2*ltj))-1;


	if (tms<=(2*ltj))
	                gl[7]=0;
	                else
					gl[7]=fabs(tms/(2*ltj))-1;


//		  els - descompressão e formação de fissura

	if (des<=0)
	              gl[8]=0;			   // els - descompressão
              else
				  gl[8]=des;


	if (ff<=(2*ltk))               // limite tração jem
	               gl[9]=0;		   // els -formação fissura
	               else
				   gl[9]=(ff/(2*ltk))-1;


//	   restrição do x dentro da peça (acima dos alvéolos)

	if (xl<=xmax[vl])
	                    gl[10]=0;		   // restrição x (dentro laje)
	                    else
       					gl[10]=(xl/xmax[vl])-1;


//		elu e beta x

	if (mresl>=mld)
	                  gl[11]=0;	           	// restrição momento
	                  else
					  gl[11]=(mld/mresl)-1;


	bxl=xl/ddl;						 // beta x laje: serão aceitos domínios 2 e 3

	if (bxl>0)
	                  gl[12]=0;
	                  else
					  gl[12]=fabs(bxl);  // evitar q bx seja negativo


     	if (bxl<=0.6)
		                gl[13]=0;
	                    else
						gl[13]=(bxl/0.6)-1;


	if (llj>=(dminx*(1-dl)+dminy*(dl)))
	                                      gl[14]=0;
	                                      else
										  gl[14]=((dminx*(1-dl)+dminy*(dl))/llj)-1;
// distância mínima entre pilares

	//           verificação flechas

	if ((ft+cft)<=(1.05*llj/250))      // margem para o deslocamento
	                                gl[15]=0;
									else
									gl[15]=((ft+cft)/(1.05*llj/250))-1;

//
//	 restrição de relação vão/altura laje (bijan)
//
	if ((llj/(hl[vl]+0.05))<=45)
    gl[16]=0;
    else
    gl[16]=((llj/(hl[vl]+0.05))/45)-1;

//
//	   somatório penalidades lajes
//

	penl=gl[0]+gl[1]+gl[2]+gl[3]+gl[4]+gl[5]+gl[6]+gl[7]+gl[8]+gl[9]+gl[10]+gl[11]+gl[12]+gl[13]+gl[14]+gl[15]+gl[16];

//
//			  VIGA "T" INVERTIDA
//
//	           Rotina de Cálculo
//
//
//	 Propriedades geométricas Viga isolada
//
    	av=((bv[vv]+0.3)*hv[vv])+(bv[vv]*(hl[vl]-0.05)); // área viga (isolada) m2
    	ppv=av*2.5;                                      // pp viga tf/m

	    me=((bv[vv]+0.3)*(pow(hv[vv],2))/2)+bv[vv]*(hl[vl]-0.05)*(hv[vv]+(hl[vl]-0.05)/2);						// momento estático

	    ygv=me/av;                                       // cg viga isolada

//	 momento inércia viga isolada

	iv=(bv[vv]+0.30)*pow(hv[vv],3)/12+(bv[vv]+0.30)*hv[vv]*pow(((hv[vv]/2)-ygv),2)+bv[vv]*pow((hl[vl]-0.05),3)/12+bv[vv]*(hl[vl]-0.05)*pow((hv[vv]+((hl[vl]-0.05)/2)-ygv),2);

//	  propriedades seção composta

	avc=av+bv[vv]*0.10; //área seção composta m2

	mec=((bv[vv]+0.3)*pow(hv[vv],2)/2)+bv[vv]*(hl[vl]-0.05)*(hv[vv]+(hl[vl]-0.05)/2)+ bv[vv]*0.10*(hv[vv]+hl[vl]+0.05);

	ygcv=mec/avc;

    ppvc=ppv+(bv[vv]*0.10*2.5);  // pp viga seção composta (tf/m)

//	 momento inércia seção composta

	ivc=(bv[vv]+0.30)*pow(hv[vv],3)/12+(bv[vv]+0.30)*hv[vv]*pow(((hv[vv]/2)-ygcv),2)+bv[vv]*pow((hl[vl]+0.05),3)/12+bv[vv]*(hl[vl]+0.05)*pow((hv[vv]+((hl[vl]+0.05)/2)-ygcv),2);


//	 excentricidades de cada camada (metro)

    	epa=ygv-0.05;
        epb=ygv-0.10;

        epca=ygcv-0.05;
        epcb=ygcv-0.10;

//	  módulo resistente



	wvi=iv/ygv;
    wvs=iv/(ygv-(hv[vv]+hl[vl]-0.05));
	wcvi=ivc/ygcv;
    wcvs=ivc/(ygcv-(hv[vv]+hl[vl]+0.05));


//	 momentos e tensões (verificação transitória na fase de montagem)

	mvt=(((rl[0]+rl[1])/1.2)*2+ppv)*pow(llv,2)/8;	// momento transitório (tf.m)
	                                            // pp e capa + ppviga

	tvi=mvt/(100*wvi);
    tvs=mvt/(100*wvs);   // tensões na seção isolada (mpa)


//	 momentos e tensões verificação transitória somente devido ao peso próprio

	mvpp=(ppv*pow(llv,2))/8;	 // momento devido ao pp da viga	(tf.m)

	tvppi=mvpp/(100*wvi);// tensões devido ao pp da viga	(mpa)

	tvpps=mvpp/(100*wvs);

//   tensoes devido ao peso de paredes sobre a viga

//	mvpar=(gpv*(llv**2))/8

//	tvpar=mvpar/(100*wcvi)

//	 momentos e tensões durante vida útil (els)
//
//  com: divide por 1.2 p/ calcular carga por metro na viga
//
//  com: multiplica por 2 p/ considerar a contribuição dos dois lados de lajes
//

	mvg=(((rl[2]+rl[3])/1.2)*2)*pow(llv,2)/(2*8); // tf.m / pav+rev+paredes na laje

	mvq=(rl[4]/1.2)*2*pow(llv,2)/(2*8);   // tf.m / sobre-carga (q)

	tvgi=mvg/(wcvi*100);	// tensões devido pav+rev+par rel. à sç composta(mpa)

	tvq=mvq/(wcvi*100);	// tensões devido à sc (q) rel. à sç composta (mpa)

//	 cálculo momento de cálculo

	mvd=(((1.3*rl[0]+1.4*rl[1]+1.4*(rl[2]/2)+1.4*(rl[3]/2)+1.4*(rl[4]/2))*(2/1.2)+1.3*ppv)*pow((llv-lp),2)/8)/100;		// momento de cálculo mn.m

//
//	reações nos pilares
//

  rpilar=((rl[0]+rl[1]+rl[2]+rl[3]+rl[4])*(2/1.2)+ppv)*llv*numpav*1.02;  // [tf]

  //   considera a carga total no pilar + 2% para o pp

  if (rpilar<=380) {
                     sp=0.16;
					 lp=0.4;
                  }
					 else
                     {
					 if (rpilar<=600) {
					                    sp=0.25;
										lp=0.5;
                                        }
										else
										{
										sp=0.36;
										lp=0.6;
                                        }
          }



//
//	  protensão em vigas
//

//	  protensão na pista (mn)

	pav=-0.97*(na[ana]+nb[anb])*0.0001014*1453;   // mn	(sinal - / compressão)

	soma=(na[ana]*epa+nb[anb]*epb)*0.97*0.0001014*1453*(-1); //(sinal -)

	soma2=(na[ana]*pow(epa,2)+nb[anb]*pow(epb,2))*0.97*0.0001014*1453*(-1);				  //(sinal -)

	sptv=(-1)*((pav/av)+(soma/wvi))+(40.966/pow(fckpm[pm],0.5))*((pav/av)+(soma2/iv));

//	 protensão após trasnferência (mn)

	pat=pav-(na[ana]+nb[anb])*0.0001014*sptv;


	soma3=pat*(float(na[ana])*epa/(float(na[ana])+float(nb[anb])))+ pat*(float(nb[anb])*epb/(float(na[ana])+float(nb[anb])));

	vtinpt=(pat/av)+(soma3/wvi);

	vtsupt=(pat/av)+(soma3/wvs);

//	 protensão em um tempo infinito (mn)

	vpinf=0.8*pav;	  // perda estimada (20%)

	vtinpi=(vpinf/av)+(0.8*soma/wvi);

	vtsupi=(vpinf/av)+(0.8*soma/wvs);


//		tensões limites

//	lcj=0.49*fckpm(pm)                 // limite compressão fckj (transitória)
	ltjv=1.5*0.7*0.3*pow((0.7*fckpm[pm]),(2/3)); // limite tração fckj(retangular)

//	lck=0.7*fckpm(pm)                // limite compressão fck   (els)
	ltkv=1.5*0.7*0.3*pow(fckpm[pm],(2/3)); // limite tração fck   (els)




//	   tensões els (mpa)

	descompv=tvi+tvgi+0.3*tvq+vtinpi;
	ffissv=tvi+tvgi+0.4*tvq+vtinpi;

//
//		tensões atuantes nas fases transitórias
//

	tdiv=vtinpt+tvppi;	// desmoldagem inferior
	tdsv=vtsupt+tvpps;	// desmoldagem superior
	ttiv=vtinpt+0.8*tvppi;	// transporte inferior 0.8
	ttsv=vtsupt+0.8*tvpps;	// transporte superior 0.8
	ttiiv=vtinpt+1.3*tvppi;	// transporte inferior 1.3
	ttssv=vtsupt+1.3*tvpps;	// transporte superior 1.3
	tmiv=vtinpi+tvi;			// montagem inferior
	tmsv=vtsupi+tvs;			// montagem superior

/////////////////////////////////////////////////////
//
//				  PROTENSÃO SUPERIOR (Considerado apenas na transitória)
//
//////////////////////////////////////////////////////

	if  (ttsv>(2*ltjv))
    {

							pats=0.85*(-0.5716);   // 4 cabos, considerando 85% (mn)
							epcv=ygv-(hv[vv]-0.05);
							epccv=ygcv-(hv[vv]-0.05);
							protsup=(pats/av)+(pats*epcv/wvs);
							ttsv=ttsv+protsup;
       }



	if (tmsv>(2*ltjv))
    {


							pats=0.85*(-0.5716);   // 4 cabos, considerando 85% (mn)
							epcv=ygv-(hv[vv]-0.05);
							epccv=ygcv-(hv[vv]-0.05);
							protsup=(pats/av)+(pats*epcv/wvs);
							tmsv=tmsv+protsup;
       }




	if (tdsv>(2*ltjv))
    {

							pats=0.85*(-0.5716);   // 4 cabos, considerando 85% (mn)
							epcv=ygv-(hv[vv]-0.05);
							epccv=ygcv-(hv[vv]-0.05);
							protsup=(pats/av)+(pats*epcv/wvs);
							tdsv=tdsv+protsup;
     }





//	   estado limite último

	ht=hv[vv]+hl[vl]+0.05; //   altura total do pavimento (m)

	da=ht-0.05;
    db=ht-0.10; // braços de alavanca (m)






//	ep=195000 // módulo aço protensão mpa
//	es=210000 // módulo aço mpa

	apa=na[ana]*0.0001014;
    apb=nb[anb]*0.0001014;

	as=npt[anpt]*bp[abp];

//
//	  rotina 2006 p cálculo de x (linha-neutra)
//		  cálculo do momento resistente
//
	xv=(1486.9*(apa+apb)+434.8*(as))/(0.4857*fckpm[pm]*bv[vv]);

	za=ht-0.05-0.4*xv;  // braço de alavanca camada a (m)
	zb=za-0.05;		   // braço de alavanca camada b (m)

	mresv=1486.9*(apa*za+apb*zb); // momento resistido pela seção (mn.m)


//////////////////////////////////////////////////////////////
//															//
//				ROTINA FLECHAS VIGAS						//
//															//
//////////////////////////////////////////////////////////////

	cfiv=(pat*epa*llv)/(8*4760*pow(fckpm[pm],0.5)*iv);

	cftv=cfiv*2.5;

	fiv=(3*((rl[0]+rl[1]+rl[2]+rl[3]+0.3*rl[4])*(2/1.2)+ppv)*pow(llv,4))/(100*384*4760*pow(fckpm[pm],0.5)*ivc);

	ftv=fiv*2.5;

//
//		 RESTRIÇÃO (Resistente tem q ser superior ao de cálculo)
//
//		 Estado em Vazio -
//

//          ZONA INFERIOR - COMPRIMIDA ?

	if (fabs(tdiv)<=lcj)
	                      gv[0]=0;
	                      else
						  gv[0]=fabs(tdiv/lcj)-1;


	if (fabs(ttiv)<=lcj)
	                       gv[1]=0;
	                       else
						   gv[1]=fabs(ttiv/lcj)-1;

	if (fabs(ttiiv)<=lcj)
	                       gv[2]=0;
	                       else
						   gv[2]=fabs(ttiiv/lcj)-1;


	if (fabs(tmiv)<=lcj)
	                       gv[3]=0;
	                       else
						   gv[3]=fabs(tmiv/lcj)-1;


//        zona superior - tracionada ?

//	if (tdsv.le.(2*ltjv)) then 	// limite sugerido jem

	if (tdsv<=pow((0.7*fckpm[pm]),0.5)) 	// limite aci
	                  gv[4]=0;
 	                 else
//					  gv(5)=abs(tdsv/(2*ltjv))-1
					  gv[4]=fabs(tdsv/pow((0.7*fckpm[pm]),0.5))-1;

//	if (ttsv.le.(2*ltjv))     then
	if (ttsv<=(pow(0.7*fckpm[pm],0.5)))
	                      gv[5]=0;
	                      else
						  gv[5]=fabs(ttsv/pow((0.7*fckpm[pm]),0.5))-1;


//	if (ttssv.le.(2*ltjv))     then
 	if (ttssv<=pow((0.7*fckpm[pm]),0.5))
	                       gv[6]=0;
	                       else
						   gv[6]=fabs(ttssv/pow((0.7*fckpm[pm]),0.5))-1;

//	if (tmsv.le.(2*ltjv))    then
	if (tmsv<=pow((0.7*fckpm[pm]),0.5))
	                     gv[7]=0;
	                     else
						 gv[7]=fabs(tmsv/pow((0.7*fckpm[pm]),0.5))-1;


//
//	     els
//

//       descompressao

	if (descompv<=0.05)    // adotado 0.05 como margem e referência
	                     gv[8]=0;
	                     else
						 gv[8]=(descompv/0.05)-1;


//	  FORMACAO DE FISSURA

	if (ffissv<=(2*ltkv)) 			   // limite tração jem
	                      gv[9]=0;			   // els - formação fissura
	                      else
						  gv[9]=(ffissv/(2*ltkv))-1;

//
//		elu e beta x
//

	if (mresv>=(0.98*mvd))
	                    gv[10]=0;					// restrição do momento
	                    else
                        {
						if (mresv<=0)
						                      gv[10]=1-(mresv/(0.98*mvd));
											  else
						                      gv[10]=fabs((0.98*mvd)/mresv)-1;
						}

	bxv=xv/da;

	if (bxv>0)
	                    gv[11]=0;				// beta x viga
	                    else
						gv[11]=fabs(bxv);

    if (bxv<=(1.02*0.6))
	                    gv[12]=0;			   // beta x viga
	                    else
						gv[12]=(bxv/(1.02*0.6))-1;


//	   geometria

    if (na[ana]<=nmax[vv])
	                    gv[13]=0;		   // qde cabos camada
	                    else
						gv[13]=(float(na[ana])/float(nmax[vv]))-1;

	if (nb[anb]<=nmax[vv])
	                    gv[14]=0;		   // qde cabos camada
	                    else
						gv[14]=(float(nb[anb])/float(nmax[vv]))-1;


    if (ht<=hmax)
	                gv[15]=0;			  // altura máxima do pavimento
	                else
					gv[15]=(ht/hmax)-1;


    if (bv[vv]<=bmax)
	                    gv[16]=0;		  // largura máxima viga
	                    else
						gv[16]=((100*bv[vv])/bmax)-1;	//teste: diminuição domínio


	if (llv>=(dminx*(dl)+dminy*(1-dl))) 		// distância mínima entre pilares
	                                      gv[17]=0;
		                                  else
						            gv[17]=((dminx*(dl)+dminy*(1-dl))/llv)-1;



	if (na[ana]>=nb[anb]) 			  // evitar mais ferros na segunda camada(nb(anb))
	              gv[18]=0;		  // em relação à primeira(na)
				  else
				  gv[18]=(float(nb[anb])/float(na[ana]))-1;

//         flechas

	if ((cftv+ftv)<=(1.05*llv/250))
	                               gv[19]=0;
								   else
								   gv[19]=((cftv+ftv)/(1.05*llv/250))-1;


//
//	   somatório penalidades vigas
//
	penv=gv[0]+gv[1]+gv[2]+gv[3]+gv[4]+gv[5]+gv[6]+gv[7]+gv[8]+gv[9]+gv[10]+gv[11]+gv[12]+gv[13]+gv[14]+gv[15]+gv[16]+gv[17]+gv[18]+gv[19];

//	   penalidade total

	pentotal=1+15*(penl+penv);    // intensidade penalização k=10

//
//		  rotina para contar elementos
//
	qdv=nx*(ny+1)*dl+ny*(nx+1)*(1-dl); // qde de vigas pavimento


//	qdv=qdv*numpav                    //qde vigas total


	//QDL=(real(NX)*LLV/1.2)*NY*DL+(real(NY)*LLV/1.2)*NX*(1-DL) ! Qde de lajes PAVIMENTO


// arredonda pra mais porque qualquer coisa vc pode cortar a laje
//if ((nx*llv/1.2)*ny*dl+(ny*llv/1.2)*nx*(1-dl)==int ((nx*llv/1.2)*ny*dl+(ny*llv/1.2)*nx*(1-dl)))
//{
	//qdl=int((nx*llv/1.2)*ny*dl+(ny*llv/1.2)*nx*(1-dl)); // qde de lajes pavimento
	qdl=(float(nx)*llv/1.2)*ny*dl+(float(ny)*llv/1.2)*nx*(1-dl);
//}
//else
//{
//     qdl=int((nx*llv/1.2)*ny*dl+(ny*llv/1.2)*nx*(1-dl))+1;
//}




//	qdl=qdl*numpav                    // qde lajes total

	qdp=(nx+1)*(ny+1); // qde de pilares

//////////////////////////////////////////////////////////////////////////////
//
//	   cálculo função aptidão
//
//	   comentário: o vão da laje é subtraído da largura da viga
//				   e o da viga do lado do pilar
//
///////////////////////////////////////////////////////////////////////////////

	vpmv=((bv[vv]+0.3)*hv[vv]+bv[vv]*(hl[vl]-0.05))*(llv-lp); // volume vigas
	vpml=a[vl]*(llj-bv[vv]);		                        // volume lajes

	vml=(lx*ly-float(qdp)*sp)*0.05+bv[vv]*0.05*(llv-lp)*qdv; // vol. capa + complemento viga

	vpmp=sp*3.5*1.15;           				 // volume pilar - 01 lance
											 // 1.15 para considerar o console

//   cálculo taxa ] pilar



if (pm>0) {

	             if (pm==1)
				              ro=120;
                 if (pm==2)
                              ro=90;
                  else
                              ro=60;

                 }
	else
				 ro=150;


//   aço demais elementos

	vapv=(na[ana]+nb[anb])*0.0001014*(llv-lp);    // volume aço protensão viga
	vapl=apl[vl]*(llj-bv[vv]);		         // volume aço protensão laje
	vadv=npt[anpt]*bp[abp]*(llv-lp);               // volume aço doce viga


///////////////////////////////////////////////////////////////////////////////////

//	       custo do concreto das vigas, complemento vigas e lajes

///////////////////////////////////////////////////////////////////////////////////

custoconc=((vpmv*cpm[pm]*qdv)*1.5+(vpml*cpm[pm]*qdl)+(vpmp*cpm[pm]*qdp*1.5))*numpav;

custoconcml=vml*ccml[cml]*1.3*numpav;

// 1.5 pq concreto viga e pilar é mais caro

// em 20/11/06 foi desconsiderado o custo fundação

	/////////////////////////////////
	// custo pilar: REVERRRRRRRRRRRRRRRRRRR
	// x 1.2 pconsiderar fundação!!!!!!!!!!!!!!!!!!!!
	////////////////////////////////

////////////////////////////////////////////////

//     custo despesas operacionais em lajes

///////////////////////////////////////////////

if (vl<28)
              dop=24;
			  else
			  dop=36;         // custos despesas operacionais unitários

cdop=qdl*(llj-bv[vv])*1.2*dop*numpav;       // custos despesas operacionais total


////////////////////////////////

//     CUSTOS TRANSPORTE

////////////////////////////////

if ((llv-lp)>12)
                    ctv=1600;
					else
					ctv=1000;

if ((llj-bv[vv])>12)
                    ctl=1600;
					else
					ctl=1000;


if (numpav>3)
                 ctp=1600;
				 else
				 ctp=1000;


ctt=(((vpmv*qdv*ctv)/10)+((vpml*qdl*ctl)/10)+((vpmp*qdp*ctp)/10))*numpav;


////////////////////////////////////////////

//     CUSTO MONTAGEM					 //

////////////////////////////////////////////

float quantviga;
float quantlaje;

quantviga=qdv;
quantlaje=qdl;

ctmv=ceil((quantviga/16)+(quantlaje/24));   // 1100 guindaste e 400 mo


// ctml=(qdl/24)*1500

ctmp=(qdp/8)*1500;

ctmt=1500*ctmv*numpav+ctmp;





/////////////////////////////////////////////////////////////////////////////////////
//
//	   CUSTOS DAS PERDAS DA PISTA E NÚMERO DE PISTAS UTILIZADAS
//
//	              OBS: ROTINA EM CONSTRUÇÃO	/ falta custo utilizaçao
//										  falta acrescentar na funcao custo
//
/////////////////////////////////////////////////////////////////////////////////////

//lpl=140                     // comprimento pista laje

//nlp=(lpl-mod(lpl,lljc))/lljc  // numero lajes por pista

//qdpl=((qdl-mod(qdl,nlp))/nlp)+1  // qde pistas p confeccionar as lajes

//if (mod(qdl,nlp).eq.0) then
//					   qdpl=qdpl-1
//					   endif

//ptal=((qdpl*lpl)-(qdl*lljc))*apl(vl)*7857 // perda do aço de protensao em kg

//lpv=60						// comprimento pista viga

//nvp=(lpv-mod(lpv,llv))/llv	// numero vigas por pista

//qdpv=((qdv-mod(qdv,nvp))/nvp)+1  // qde de pistas p confeccionar as vigas

//if (mod(qdv,nvp).eq.0) then
//                       qdpv=qdpv-1
//					   endif

//ptav=((qdpv*lpv)-(qdv*llv))*(na(ana)+nb(anb))*0.0001014*7810	// perda aço de prot em kg



//////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////
//
//	                        Custo Aços: PROTENSÃO E PASSIVO
//
//////////////////////////////////////////////////////////////////////

	custoprot=(1.085*vapv*7810.65*qdv+vapl*7857*qdl)*cap*numpav;


	custoad=(vadv*7760*qdv*cad+vpmp*ro*qdp*cad)*numpav;

	custocis=5.6*(((bv[vv]-0.05)+(hv[vv]-0.05))*2+0.12)*bv[vv]*(llv-lp)*qdv*cad*numpav;

	custope=0.86912*(llv-lp)*qdv*numpav*cad;  // custo porta estribo 4 6mm

	custolig=12.125*qdp*numpav*cad;        // custo arm ligação 5 12.5mm (c=2,5 m)

	custoneo=qdp*2*numpav*22.5;   // r$ 22.5

// 1.085 pq cordoalha em viga é mais cara


///////////////////////////////////////////////////////////////////

//	                     CUSTO TOTAL MATERIAIS

///////////////////////////////////////////////////////////////////

	custofab=(custoconc+custoprot+custoad+cdop+custocis+custope)*1.33;

	custotal=(custofab+custoconcml+ctt+ctmt+custoneo+custolig)/numpav;

	float f=0;

	f=custotal*pentotal;

	if(k==0){



    cout <<"      LAJE ALVEOLAR    "<<endl<<endl;
	cout <<" NX:  "<< nx<< endl<<endl;
	cout <<" NY:  "<< ny<< endl<<endl;
	cout <<" DL:   " << dl<< endl<<endl;

	cout <<" FCKCML:   " << fckml[cml]<< endl<<endl;
	cout <<" FCKCPM:   " << fckpm[pm]<< endl<<endl;

	cout <<" HL:   "<< hl[vl]<<endl<<endl;
	cout <<" LLJ:   " << llj<< endl<<endl;
	cout <<" HV:   " << hv[vv]<< endl<<endl;
	cout <<" BV:   "<< bv[vv]<<endl<<endl;
	cout <<" LLV:   " << llv<< endl<<endl;
	cout <<" NA:  "<< na[ana]<< endl<<endl;
	cout <<" NB:  "<< nb[anb]<< endl<<endl;
    cout <<" NPT:  "<< npt[anpt]<< endl<<endl<<endl;


    cout << "somatorio penalidade da laje   :"<<penl<<endl;
    cout << "somatorio penalidade das vigas   :"<< penv<<endl;
	cout << "penalidade total:    "<<pentotal<<endl<<endl;
	cout << "custo concreto:  "<< custoconc <<endl;
	cout << "custo protensao:    "<<custoprot<<endl;
	cout <<"custo transporte:   "<< ctt <<endl;
	cout <<"custo montagem:   "<< ctmt <<endl;
	cout <<"custo despesas operacionais:   "<< cdop <<endl;
	cout << "custo total:    "<<custotal<<endl;
	cout <<"custo aptidao:   "<< f <<endl<<endl;


	 cout <<"--- DADOS DA LAJE INDIVIDUO   1 ---"<<endl;
     cout <<"VL = "<<vl<<endl;
     cout <<"LP = "<<lp<<endl;
	cout <<"contra-flecha total (laje): "<<cft<<endl;
	cout <<"flecha total(laje) : "<<ft<<endl<<endl;


     cout <<"--- DADOS DA VIGA INDIVIDUO   1 ---"<<endl;
     cout<<"VV = "<<vv<<endl;
     cout <<"QDV = "<<qdv<<endl;
     cout <<"QDP = "<<qdp<<endl;
     cout <<"QDL = "<<qdl<<endl;
     cout <<"contra-flecha total (viga): "<< cftv<<endl;
     cout <<"flecha total(viga) :"<<ftv<<endl<<endl;


    }
return f;

//       Com: Valor que será jogado no vetor APT(k) do Main Program AG.f90



// Apresentação dos valores encontrados para cada indivíduo
//		WRITE (*, '(1X,A,I3,A)') "--- Individuo ", K, " ---"
//		WRITE (*, '(/)', ADVANCE = "NO")
//
//		DO p=1,numgen
//
//			WRITE (*, '(I1)', ADVANCE = "NO") apop(K,p)
//
//		END DO





//		PAUSE 'Pressione ENTER para continuar.'



                        }

float AvaliaIndividuoTT (float dminx, float dminy, float lx, float ly, float hmax,float bmax, float q, float gpr, float gpl, float cap, float cad, int ptamanho, int nxmax, int nymax, int nvv, int numgen, int k, int numpav,individuo pop[] )
{

// F                = Função aptidão
// Custo total      = Função objetivo (sem as restrições)
// k                = indica os indivíduos a serem avaliados

//Contadores inteiros

   int i,j,p;
   int apop[ptamanho][numgen];


/*------------------------------------------------------------------------------


    O k é o indivíduo que está sendo analisado no momento
    numgen é o número de bits do genótipo (cromossomo)			*/

            for (j=0; j<numgen; j++)
            {
                apop[k][j]=pop[k].binario[j];

            }


//------------------------------------------------------------------------------

    float ccml[4];
    float cpm[4];

//------------------------------------------------------------------------------


//                      CUSTO CONCRETO MOLDADO NO LOCAL (cml)


	ccml[0]=147;
	ccml[1]=158;
	ccml[2]=171;
	ccml[3]=185;

//------------------------------------------------------------------------------

//                      CUSTO CONCRETO PRÉ-MOLDADO  (cpm)

   cpm[0]=185;
   cpm[1]=200;
   cpm[2]=216;
   cpm[3]=233;

/*-------------------------------------------------------------------------------

                          Definição Variáveis lOCAIS
	                        Variáveis de Projeto (VP)
	                Variáveis da configuração estrutural
*/


	int nx,ny;                // Número de vãos na direção X e Y	- VP
	int dl;                   // Direção da laje: 1 (direção Y) e 0 (direção X) - VP
	float ajx,ajy;

//------------------------------------------------------------------------------


//	                         Variáveis Auxiliares


	float llj,llv,rpilar;     // Vão da laje e vão da viga E REACAO NO PILAR
	float lp,sp;  		      // LP= Lado pilar SP=SEÇÃO DO PILAR
	float ro;			      // TAXA AÇO PILAR
	float lljc;               // Vão da laje corrigido (descontado BV)


//------------------------------------------------------------------------------


//	                       Variáveis do material



	int fckml[4];             // Fck moldado in loco
    int fckpm[4];             // Fck pré-moldado
	int	pm,cml;               // Contadores dos fcks - VP


//------------------------------------------------------------------------------

//	                      Variáveis Quantidade Peças


	int  qdp, qdl, qdv;            // Quantidade de pilar, laje e viga respectivamente


//------------------------------------------------------------------------------

//                           Variáveis dos custos


	float dop, cdop;                          // DESPESAS OPERACIONAIS LAJES
	float ctv, ctl, ctp, ctt;                 // CUSTOS TRANSPORTE
	float ctmv, ctml, ctmp, ctmt,custoneo;    // CUSTOS MONTAGEM


//------------------------------------------------------------------------------

//	                         Variáveis da Laje
//	                      Variáveis de Projeto: VL

	int vl;                  // Caracteriza a laje
	float ll[8];             // Largura da laje (m)
 	float hl[8];	         // altura da laje(m) (nervura+mesa)
    float bl[8];             // base da laje(m);
    float hml[8];            // altura mesa da laje(m)
    float hdl[8];            // altura do dente(m)
    float ldma[8];           // largura do dente maior(m)
    float ldme[8];           // largura dente menor(m)
    float pa[8];             // Força Protensão antes transferência (MN)
	float apl[8];			 // apl Área de Protensão na Laje (m2)

//------------------------------------------------------------------------------


//	                           Variáveis Auxiliares


	float m,ac,ygc;                                 // relação fcks, área capa corrigida, cg sç composta
	float ic;                                       // Momento inércia sç composta
	float yg[8],a[8],ii[8],xmax[8];                 // dados seção isolada
	float ys[8];                                    // distância do cg das cordoalhas (de baixo pra cima)
	float nc[8], dc[8];                             // número e diâmetro dos cabos
	float ep,epc,winf,wsup,wcinf,wcsup;             // excentricidades e módulos LAJES
	float carga[6],ml[6],rl[6];                     // Auxiliares cálculo esforços
	float mld,vld;                                  // Momento e cortante de cálculo (faixa de 1.2m)
	float tinf,tsup,tcinf,tcsup;                    // Tensões na LAJE
	float scp,spt,pt,pinf;                          // Auxiliares na protensão
	float tinpt,tsupt,tinpi,tsupi;	                // Tensões protensão
	float tdesi,tdess,tti,tts,ttii,ttss,tmi,tms;    // Tensões atuantes transitórias
	float des,ff,lcj,ltj,lck,ltk;                   // tensões limites
	float xtl,xl,zl,zla,zlb,mresl;                  // auxiliares elu
	float bxl, ddl, penl;                           // beta x da laje, altura útil laje e penalidade laje
	float cfi, cft, fi, ft, eil;                    // Contra-flecha e flecha das lajes


//------------------------------------------------------------------------------

//	                        VARIÁVEIS DA VIGA
//	                     VARIÁVEIS DE PROJETO: vv

	int vv;
	float hv[32],bv[32];          // geometria da viga
	float ht;                     // altura total do pavimento
	int nmax[32];  	              // qde máx. de cordoalha por camada
	int ana,anb,nbaux;            // qde de cordoalhas por camada
	int na[16];
    int nb[16];
	int npt[4];                   // qde de barras passivas de tração
 	float bp[4];                  // bitolas passivas

//------------------------------------------------------------------------------

//	               VARIÁVEIS AUXILIARES (GEOMETRIA E TENSÕES)


	float av,ppv,me,ygv,iv;                    // área, peso próprio, mom. estático,cg, m. inércia
	float avc,ppvc,mec,ygcv,ivc;               // dados sç composta
	float epa,epb,epcv;                        // excentricidade sç isolada
	float epca,epcb,epccv;                     // excentricidade sç composta
	float da,db,apa,apb,as;                    // altura útil e área de armaduras
	float wvi,wvs,wcvi,wcvs;                   // módulos resistentes
	float mvt,mvpp,mvg,mvq,mvd;                // momentos
	float tvi,tvs,tvppi,tvpps,tvgi,tvq;        // tensões
	float bxv,penv;                            // beta x viga e penalidade viga
	int anpt,abp;						       // auxiliares contador

//------------------------------------------------------------------------------


//				          VARIÁVEIS AUXILIARES (PROTENSÃO)

	float pav,soma,soma2,sptv,pat,soma3,pats,protsup;
	float vtinpt,vtsupt,vpinf,vtinpi,vtsupi;
	float ltjv,ltkv,descompv,ffissv;
	float tdiv,tdsv,ttiv,ttsv,ttiiv,ttssv,tmiv,tmsv;

//------------------------------------------------------------------------------


//		               	VARIÁVEIS AUXILIARS (ELU) / (ELS)

	float xv,za,zb,mresv;
	float cfiv,cftv, fiv, ftv;


//------------------------------------------------------------------------------

//                                                                              >>VER AS RESTRIÇÕES

//			             VARIÁVEIS DAS RESTRIÇÕES

	float gl[17];  //restrições lajes
	float gv[20];  //restrições vigas

//------------------------------------------------------------------------------

//		     	        VARIÁVEIS APTIDÃO / CUSTOS

	float  vpmv,vpml,vpmp,vml,vapv,vapl,vadv;                            // volume dos materiais
	float  custoconc, custoconcml,custoprot,custoad,custotal, custofab;  // custos material
	float  custocis,custope,custolig;
	float  pentotal;                                                     // somatório penalidades
	float  lpl,nlp,qdpl,ptal,lpv,nvp,qdpv,ptav;


/*------------------------------------------------------------------------------

                            BANCO DE DADOS

    		     Listas das Variáveis dos Materiais
                   Resitências Materiais (fcks)                                */



	for(i=0;i<4;i++)
    {

	fckpm[i]=35+(i)*5;	 //  35,40,45,50 (valores fckpm)

	fckml[i]=20+(i)*5;	 //  20,25,30,35	(valores fckml)
	}

/*------------------------------------------------------------------------------



		           	        LISTAS LAJES

            	  Vinculação da variável VL das Lajes
	              Propriedades geométricas das Lajes

             Definição propriedades da laje seção PM - ACI
				           Banco Dados - Laje                                 */

// 8 opções de lajes
                          // Geometria 0,61 X 2,44


                              // |----------|
                              //  \_/----\_/

           ll[0]=2.44;              //largura da laje (m)
	       hl[0]=0.61;	            // altura da laje(m) (nervura+mesa)
	       hml[0]=0.05;             // altura mesa da laje(m)
	       hdl[0]=0.56;             // altura do dente(m);
           ldma[0]=0.15;            // largura do dente maior(m);
           ldme[0]=0.1;             // largura do dente menor(m)
           a[0]=0.26;	            // área da laje (m2)
           yg[0]=0.44;		        // cg da laje (m)
	       ii[0]=0.008734616;       // momento de inércia da laje (m4)
           //xmax[i]=0.065;         // máximo x (ln)
           nc[0]=6;                 // número de cabos                           << usar para achar força de protensão?? como ?
           dc[0]=0.0127;            // diâmetro do cabo(m)
           ys[0]=0.18;


           ll[1]=2.44;
	       hl[1]=0.61;
	       hml[1]=0.05;
	       hdl[1]=0.56;
           ldma[1]=0.15;
           ldme[1]=0.1;
           a[1]=0.26;
           yg[1]=0.44;
	       ii[1]=0.008734616;
           //xmax[i]=0.065;
           nc[1]=8;
           dc[1]=0.0127;
           ys[1]=0.20;

           ll[2]=2.44;
	       hl[2]=0.61;
	       hml[2]=0.05;
	       hdl[2]=0.56;
           ldma[2]=0.15;
           ldme[2]=0.1;
           a[2]=0.26;
           yg[2]=0.44;
	       ii[2]=0.008734616;
           //xmax[i]=0.065;
           nc[2]=10;
           dc[2]=0.0127;
           ys[2]=0.23;

           ll[3]=2.44;
	       hl[3]=0.61;
	       hml[3]=0.05;
	       hdl[3]=0.56;
           ldma[3]=0.15;
           ldme[3]=0.1;
           a[3]=0.26;
           yg[3]=0.44;
	       ii[3]=0.008734616;
           //xmax[i]=0.065;
           nc[3]=12;
           dc[3]=0.0127;
           ys[3]=0.25;

           //Geometria 0,8 X 2,4


           ll[4]=2.44;
	       hl[4]=0.81;
	       hml[4]=0.05;
	       hdl[4]=0.76;
           ldma[4]=0.2;
           ldme[4]=0.12;
           a[4]=0.37;
           yg[4]=0.54;
	       ii[4]=0.02308586;
           //xmax[i]=0.065;
           nc[4]=12;
           dc[4]=0.0127;
           ys[4]=0.10;

           ll[5]=2.44;
	       hl[5]=0.81;
	       hml[5]=0.05;
	       hdl[5]=0.76;
           ldma[5]=0.2;
           ldme[5]=0.12;
           hl[5]=0.81;
           a[5]=0.37;
           yg[5]=0.54;
	       ii[5]=0.02308586;
           //xmax[i]=0.065;
           nc[5]=14;
           dc[5]=0.0127;
           ys[5]=0.13;

           ll[6]=2.44;
	       hl[6]=0.81;
	       hml[6]=0.05;
	       hdl[6]=0.76;
           ldma[6]=0.2;
           ldme[6]=0.12;
           hl[6]=0.81;
           a[6]=0.37;
           yg[6]=0.54;
	       ii[6]=0.02308586;
           //xmax[i]=0.065;
           nc[6]=16;
           dc[6]=0.0127;
           ys[6]=0.15;

           ll[7]=2.44;
	       hl[7]=0.81;
	       hml[7]=0.05;
	       hdl[7]=0.76;
           ldma[7]=0.2;
           ldme[7]=0.12;
           hl[7]=0.81;
           a[7]=0.37;
           yg[7]=0.54;
	       ii[7]=0.02308586;
           //xmax[i]=0.065;
           nc[7]=18;
           dc[7]=0.0127;
           ys[7]=0.18;



/*-----------------------------------------------------------------------------------

	                	     Força de protensão (MN) - lajes
	                        pa=n.diâmetroacor.1453.0,97.(10-6)

		                         sinal (-) / compressão
*/


pa[0]=-1.071237882;
pa[1]=-1.428317176;
pa[2]=-1.78539647;
pa[3]=-2.142475764;
pa[4]=-2.142475764;
pa[5]=-2.499555058;
pa[6]=-2.856634352;
pa[7]=-3.213713647;


//	           Área de protensão total no painel da laje  númerode coodoalhas*área


apl[0]=0.000760061;
apl[1]=0.001013415;
apl[2]=0.001266769;
apl[3]=0.001520122;
apl[4]=0.001520122;
apl[5]=0.001773476;
apl[6]=0.00202683;
apl[7]=0.002280184;


//---------------------------------------------------------------------------------

//      	 listas das variáveis vigas


//      	 qde de barras passivas de tração

      npt[0]=0;
      npt[1]=2;
      npt[2]=4;
      npt[3]=6;

//	    área das bitolas passivas disponíveis

     	bp[0]=0.000028;   // 6.0mm
    	bp[1]=0.000050;	 // 8.0mm
    	bp[2]=0.000080;  // 10.0mm
    	bp[3]=0.000125;  // 12.5mm

//       qde de cabos camada "a"

	   na[0]=3;
       na[1]=5;
       na[2]=6;
       na[3]=7;
	   na[4]=8;
       na[5]=10;
       na[6]=13;
       na[7]=14;
	   na[8]=15;
       na[9]=16;
       na[10]=17;
       na[11]=18;
	   na[12]=19;
       na[13]=20;
       na[14]=21;
       na[15]=23;

//      qde de cabos camada "b"

	  nb[0]=3;
      nb[1]=5;
      nb[2]=6;
      nb[3]=7;
      nb[4]=8;
      nb[5]=10;
      nb[6]=13;
      nb[7]=14;
	  nb[8]=15;
      nb[9]=16;
      nb[10]=17;
      nb[11]=18;
	  nb[12]=19;
      nb[13]=20;
      nb[14]=21;
      nb[15]=23;

//
//		características geométricas da viga
//

      for(i=0; i<5; i++){
     	hv[i]=0.20+(i)*0.05;			 // altura
     	hv[i+5]=hv[i];
    	hv[i+10]=hv[i];
     	hv[i+15]=hv[i];
    	hv[i+20]=hv[i];
		hv[i+25]=hv[i];

    	bv[i]=0.40;	 // base
    	bv[i+5]=0.50;
    	bv[i+10]=0.60;
    	bv[i+15]=0.70;
    	bv[i+20]=0.80;
		bv[i+25]=0.90;

    	nmax[i]=13;	 // qde máxima de cordoalhas por base de viga
    	nmax[i+5]=15;
    	nmax[i+10]=17;
    	nmax[i+15]=19;
    	nmax[i+20]=21;
		nmax[i+25]=23;
	  }

//   complemento das listas das vigas (32 possíveis)

		hv[30]=hv[28];
        bv[30]=bv[28];
        nmax[30]=nmax[28];
		hv[31]=hv[29] ; //
        bv[31]=bv[29];
        nmax[31]=nmax[29];

//----------------------------------------------------------------------------------


//
//             	               ROTINA PARA DECODIFICAÇÃO
//
//	           Com: As variáveis que começam com "A" são auxiliares
//
//	        Com: Este "K" vem do Loop no programa principal (k=1 até numind)
//


	dl=apop[k][0];                                     // já é o próprio valor

	pm=2*apop[k][1]+1*apop[k][2];   // auxiliar

//	cout<<fckpm[pm]<<endl;

	cml=2*apop[k][3]+1*apop[k][4];   // auxiliar

	//cout<<fckml[cml]<<endl;

	vl=4*apop[k][7]+2*apop[k][8]+1*apop[k][9];	 // auxiliar varia de 0 à 7 ([k][5] e [k][6] estão temporariamente inúteis para essa aplicação)


	anpt=2*apop[k][10]+1*apop[k][11] ;        // auxiliar lista npt

	abp=2*apop[k][12]+1*apop[k][13];                      // auxiliar p a lista bp

	ana=8*apop[k][14]+4*apop[k][15]+2*apop[k][16]+1*apop[k][17];	 // auxiliar

	anb=8*apop[k][18]+4*apop[k][19]+2*apop[k][20]+1*apop[k][21];				 // auxiliar

	nx=0;

	for(i=0; i<nxmax; i++)
    {

	nx=int(nx+apop[k][21+i+1]*pow(2,(nxmax-i-1)));

	}

	nx=nx+1;

	ny=0;

	for(i=0; i<nymax; i++)
    {
             // a função int arredonda pra baixo mas há o nx+1;

	ny=int(ny+apop[k][21+nxmax+i+1]*pow(2,(nymax-i-1)));

	}

	ny=ny+1;

	vv=0;

	for(i=0; i<nvv; i++)
    {


	vv=int(vv+apop[k][21+nxmax+nymax+i+1]*pow(2,(nvv-i-1)));

	}

//-----------------------------------------------------------------------------------


/*
!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
!
!                     REDUÇÃO DO DOMÍNIO DA BASE
!
!                   TÉCNICA: ALTERAR O VALOR DE VV
!
!	EXISTE UM ESPAÇO INFACTÍVEL MAS FAZ-SE TRANSFORMACAO NA LISTA
!
!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
*/

	if (bmax==0.40)
    {
					  if (vv>5) {
					               if (vv<11)
			                       vv=vv-5;
						           else
                                   vv=vv-10;

					             }
	}


	if (bmax==0.50)  {
	                   if (vv>10)  {
					                  vv=vv-5;
					                }
  	}

	if (bmax==0.60)
    {
	                   if (vv==16)  {
					                  vv=15;
                                      }

	}

	if (bmax==0.70)
    {
					  if (vv>20)
                      {
					               if (vv<26)
                                   vv=vv-5;
						           else
			                       vv=vv-10;

					  }
}

	if (bmax==0.80)
    {
	                   if (vv>25)
	                   {
					                  vv=vv-5;
					   }
	}


/*
!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
!
!			  AJUSTE DO NA P NAO ULTRAPASSAR O NMAX
!
!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
*/

	if (na[ana]>nmax[vv]){
	                           na[ana]=nmax[vv];
                         }


	if (nb[anb]>nmax[vv])
                        {
	                           nb[anb]=nmax[vv];
                         }



/*
!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
!																		   !
!							TRANSGÊNICO (NA x NB)
!
!	           Troca por um fenótipo que melhor se adapte ao problema
!																		   !
!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

/*
!	if (nb(anb).gt.na(ana)) then
!	              nbaux=nb(anb)
!				  nb(anb)=na(ana)
!				  na(ana)=nbaux
!				  endif

                        !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
                        !							   !
                        !   Ajuste dos Vãos Mínimos
                        !
                        !   Penaliza exageradamente
                        !
                        !							   !
                        !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!*/


ajx=lx/dminx;

 if (nx>ajx)   {
                  nx=nx*100;
                  }

 ajy=ly/dminy;

 if (ny>ajy)   {
                  ny=ny*100;
                  }


//       cálculo dos vãos

	llj=(lx/nx)*(1-dl)+(ly/ny)*(dl);		 // (m)
	llv=(lx/nx)*(dl)+(ly/ny)*(1-dl);		 // (m)



	lljc=llj-bv[vv];      // vão laje corrigido (m)






//--------------------------------------------------------------------------------


/*|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||
|                        LAJES TT                           |
|                                                           |
|		            Rotina de Cálculo                       |
|                                                           |
|	  Comentário: A tração tem sinal + e a compressão -     |
|                                                           |
|                                                           |
|          Definição propriedades seção composta da Laje    |
|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||*/

//    Cálculo do ygc, ac e ic m

    m=pow((float(fckml[cml])/float(fckpm[pm])),0.5);                         // relação fck

    ac=0.05*ll[vl];                                                          //área seção composta     (m2)

    ygc=((yg[vl]*a[vl])+(ac*(hl[vl]+0.025)))/(a[vl]+ac);                     //cg com capeamento       (m)

float auxiliar_altura, auxiliar_inercia;

    ic=ii[vl] + (ll[vl]*pow(0.05,3))/12 + ac*pow((hl[vl]+0.025-ygc),2);          // inércia seção composta (m4)


//---------------------------------------------------------------------------------------------------------
//		 excentricidades e módulos resistentes das lajes

	ep=yg[vl]-ys[vl];	                                        // (m) seção isolada, adotado cl=1,2cm
	epc=ygc-ys[vl];	                                        // (m) seção composta

//----------------------------------------------------------------------------------------------------------

	winf=ii[vl]/yg[vl];
	wsup=ii[vl]/(yg[vl]-hl[vl]);
 	wcinf=ic/ygc;
	wcsup=ic/(ygc-hl[vl]-0.05);

if (k==0){

    cout<<"winf="<<winf<<endl;
    cout<<"wsup="<<wsup<<endl;
    cout<<"wcinf="<<wcinf<<endl;
    cout<<"wcsup="<<wcsup<<endl;

    }
//--------------------------------------------------------------------------------------------------------

//                Cálculo dos momentos e tensões nas Lajes
//	                     Com: Cálculo por painel


	carga[0]=a[vl]*2.5;	          // peso próprio laje (tf/m)
	carga[1]=0.125*ll[vl];        // peso capa (tf/m),          onde 0,125 é massa específica do concreto x espessura da capa = 2,5*0,05
	carga[2]=gpr*ll[vl];	      // pav+rev	  (tf/m)
	carga[3]=gpl*ll[vl];	      // paredes sobre laje (tf/m)
	carga[4]=q*ll[vl];		      // carga acidental	(tf/m)
	carga[5]=0.05*ll[vl];         // carga de trabalho sobre a laje (tf/m) (50kg/m2)


	for (i=0; i<6 ; i++)
	{

	ml[i]=carga[i]*pow(lljc,2)/8;	 // momento em tf.m/(b
	rl[i]=carga[i]*(llj)/2  ;     // reação/cortante (tf) por painel
	}

//--------------------------------------------------------------------------------------------------------

//	   Ações de Cálculo por painel (MN.m e MN)

	mld=(1.3*ml[0]+1.4*(ml[1]+ml[2]+ml[3]+ml[4]))/100; // mom. de cálculo  laje
	vld=(1.3*rl[0]+1.4*(rl[1]+rl[2]+rl[3]+rl[4]))/100; // cortante de cálc. laje


//         Tensões Fase de concretagem (peça isolada)
//
//		   Tf/100=MN

	tinf=((ml[0]+ml[1]+ml[5])/winf)/100;   // (mpa)
	tsup=((ml[0]+ml[1]+ml[5])/wsup)/100;	  // (mpa)

//		Tensões após concretagem (seção composta)

	tcinf=((ml[2]+ml[3]+ml[4])/wcinf)/100;	// (mpa)
	tcsup=((ml[2]+ml[3]+ml[4])/wcsup)/100;	// (mpa)

//--------------------------------------------------------------------------------------------------------

//	                     Força de Protensão

//	      protensão inicial - ato da transferência (pa)
//
//	  pa=nc*acor*1453*0.97   // força de protensão inicial (mn)
//
//	  nc*acor=pa/0.001409


//	  protensão após transferência (pt)

	scp=(pa[vl]/a[vl])+pa[vl]*(pow(ep,2)/ii[vl]); // mpa (sinal -)

	spt=(-1)*((pa[vl]/a[vl])+pa[vl]*(ep/winf))+(195000/(0.85*5600*(pow(fckpm[pm],0.5))))*scp;	 // (sinal -)

	pt=pa[vl]-apl[vl]*spt;	// mn

//	  restrição - término da protensão

//	  protensão tempo infinito (pinf)

	pinf=0.75*pa[vl];		 // perda estimada (75% da força inicial)

//	  tensões devido à protensão

	tinpt=(pt/a[vl])+pt*(ep/winf);	  // tensões na seção pm após
	tsupt=(pt/a[vl])+pt*(ep/wsup);	  // transferência da protensão

	tinpi=(pinf/a[vl])+pinf*(ep/winf);  // tensõe na seção pm num tempo infinito
	tsupi=(pinf/a[vl])+pinf*(ep/wsup);

//--------------------------------------------------------------------------------------------------------

//        restrições - verificações em vazio
//         tensões atuantes em vazio (mpa)

  	tdesi=tinpt+(ml[0]/winf)/100;     // desmoldagem inferior
	tdess=tsupt+(ml[0]/wsup)/100;     // desmoldagem superior
	tti=tinpt+0.8*(ml[0]/winf)/100;   // transporte inferior (0.8)
	tts=tsupt+0.8*(ml[0]/wsup)/100;   // transporte superior (0.8)
	ttii=tinpt+1.3*(ml[0]/winf)/100;  // transporte inferior (1.3)
	ttss=tsupt+1.3*(ml[0]/wsup)/100; // transporte superior (1.3)
	tmi=tinpt+tinf;                   // montagem inferior
	tms=tsupt+tsup; 		             // montagem superior

//	  tensões els  (mpa)
//	  descompressão

	des=((ml[0]+ml[1])/winf)/100+tinpi+((ml[2]+ml[3])/wcinf)/100+0.3*(ml[4]/wcinf)/100;

//	 formação de fissura (mpa)

	ff=((ml[0]+ml[1])/winf)/100+tinpi+((ml[2]+ml[3])/wcinf)/100+0.4*(ml[4]/wcinf)/100;

//******************************************************************************************

//mudar ?
//		tensões limites

	lcj=0.49*fckpm[pm];                 // limite compressão fckj (transitória)
	ltj=1.2*0.7*0.3*pow((0.7*fckpm[pm]),(2/3)); // limite tração fckj

	lck=0.7*fckpm[pm];                // limite compressão fck   (els)
	ltk=1.2*0.7*0.3*pow((fckpm[pm]),(2/3)); // limite tração fck / seção "t" (els)


//*******************************************************************************************
//
//		 solicitações normais - elu	(lajes alveolares)
//
//	 obs: será testada a roti na que não necessita do cálculo do pré
//		  alongamento
//

	ddl=(hl[vl]+0.03875);  // altura útil da laje simplificada

	xtl=(3061.38/ll[vl])*apl[vl]/fckml[cml]; // para o painel b=1.2m
// 3061.38 = ((1710*1.4)/(0.68*1.15))

	if (xtl<=0.05)
    {

	xl=xtl;
	zl=ddl-0.4*xl;
	mresl=apl[vl]*1486.9*zl;
    }

	else{

	xl=((1486.9*apl[vl]-0.02428*ll[vl]*fckml[cml])/(0.48571*ll[vl]*fckpm[pm]))+0.05;
	zla=ddl-0.4*xl;
	zlb=ddl-0.02;
	mresl=(0.02428*ll[vl]*fckml[cml]*zlb)+(0.48571*ll[vl]*fckpm[pm]*(xl-0.05)*zla);
    }



/////////////////////////////////////////////////////////////////////////////
//																		  //
//                     ROTINA FLECHAS EM LAJES							  //
//																		  //
/////////////////////////////////////////////////////////////////////////////

//                     CONTRA-FLECHA (PROTENSÃO)

	cfi=(pa[vl]*ep*lljc)/(8*4760*pow(fckpm[pm],0.5)*ii[vl]); // contra-flecha inicial

	cft=cfi*2.2;   // estimativa contra-flecha total (sinal"-")


//                         FLECHA  (CARREGAMENTO)

	fi=3*(carga[0]+carga[1]+carga[2]+carga[3]+0.3*carga[4])*pow(lljc,4)/100;

	eil=(384*4760*pow(fckpm[pm],0.5)*ic);   // flecha inicial (sç composta)



	ft=(fi/eil)*2.5;   // estimativa flecha total (sinal "+")
					  // total=2.5*inicial

//--------------------------------------------------------------------------------------------------------
//
//		                  RESTRIÇÕES
//
//	    Restrições estado vazio - Inferior (comprimida)
// 		 Em módulo p compensar o sinal (-) compressão
//
// Obs: Alguns valores referências são multiplicados p aumentar a margem
//

	if (fabs(tdesi)<=lcj)
	                       gl[0]=0;
	                       else
						   gl[0]=fabs(tdesi/lcj)-1;


	if (fabs(tti)<=lcj)
		                     gl[1]=0;
	                         else
							 gl[1]=fabs(tti/lcj)-1;



	if (fabs(ttii)<=lcj)
	                      gl[2]=0;
	                      else
						  gl[2]=fabs(ttii/lcj)-1;

	if (fabs(tmi)<=lcj)
	                     gl[3]=0;
	                     else
						 gl[3]=fabs(tmi/lcj)-1;

//	  restrições em vazio - superior (tracionada)
//		  não precisa ser em módulo

	if (tdess<=(2*ltj))
                    gl[4]=0;
                    else
                    gl[4]=fabs(tdess/(2*ltj))-1;


//	if (tts.le.(2*ltj)) then
    if (tts<=pow((0.7*fckpm[pm]),0.5))  // limite aci

	                gl[5]=0;
	                else
					gl[5]=fabs(tts/pow((0.7*fckpm[pm]),0.5))-1;


	if (ttss<=(2*ltj))
                    gl[6]=0;
                    else
                    gl[6]=fabs(ttss/(2*ltj))-1;


	if (tms<=(2*ltj))
	                gl[7]=0;
	                else
					gl[7]=fabs(tms/(2*ltj))-1;


//		  els - descompressão e formação de fissura

	if (des<=0)
	               gl[8]=0;			   // els - descompressão
                   else
				   gl[8]=des;


	if (ff<=(2*ltk))               // limite tração jem
	               gl[9]=0;		   // els -formação fissura
	               else
				   gl[9]=(ff/(2*ltk))-1;


//	   restrição do x dentro da peça (acima dos alvéolos)

	/*if (xl<=xmax[vl])
	               gl[10]=0;		   // restrição x (dentro laje)
                   else
                   gl[10]=(xl/xmax[vl])-1;*/


//		elu e beta x

	if (mresl>=mld)
                  gl[11]=0;	           	// restrição momento
	              else
                  gl[11]=(mld/mresl)-1;


	bxl=xl/ddl;						 // beta x laje: serão aceitos domínios 2 e 3

	if (bxl>0)
	              gl[12]=0;
	              else
                  gl[12]=fabs(bxl);  // evitar q bx seja negativo


    if (bxl<=0.6)
                  gl[13]=0;
	              else
                  gl[13]=(bxl/0.6)-1;


	if (llj>=(dminx*(1-dl)+dminy*(dl)))

	               gl[14]=0;
	               else
                   gl[14]=((dminx*(1-dl)+dminy*(dl))/llj)-1;
// distância mínima entre pilares

//           verificação flechas

	  if ((ft+cft)<=(1.05*llj/250))      // margem para o deslocamento
	                gl[15]=0;
					else
					gl[15]=((ft+cft)/(1.05*llj/250))-1;

//
//	 restrição de relação vão/altura laje (bijan)
//
	if ((llj/(hl[vl]+0.05))<=45)
                    gl[16]=0;
                    else
                    gl[16]=((llj/(hl[vl]+0.05))/45)-1;

//
//	   somatório penalidades lajes
//



	penl=gl[0]+gl[1]+gl[2]+gl[3]+gl[4]+gl[5]+gl[6]+gl[7]+gl[8]+gl[9]+gl[11]+gl[12]+gl[13]+gl[14]+gl[15]+gl[16];


//--------------------------------------------------------------------------------------------------------


//
//			  VIGA "T" INVERTIDA
//
//	           Rotina de Cálculo
//
//
//	 Propriedades geométricas Viga isolada
//
    	av=((bv[vv]+0.3)*hv[vv])+(bv[vv]*(hl[vl]-0.05)); // área viga (isolada) m2
    	ppv=av*2.5;                                      // pp viga tf/m

	    me=((bv[vv]+0.3)*(pow(hv[vv],2))/2)+bv[vv]*(hl[vl]-0.05)*(hv[vv]+(hl[vl]-0.05)/2);						// momento estático

	    ygv=me/av;                                       // cg viga isolada

//	 momento inércia viga isolada

	iv=(bv[vv]+0.30)*pow(hv[vv],3)/12+(bv[vv]+0.30)*hv[vv]*pow(((hv[vv]/2)-ygv),2)+bv[vv]*pow((hl[vl]-0.05),3)/12+bv[vv]*(hl[vl]-0.05)*pow((hv[vv]+((hl[vl]-0.05)/2)-ygv),2);

//--------------------------------------------------------------------------------------------------------


//	  propriedades seção composta

	avc=av+bv[vv]*0.10; //área seção composta m2

	mec=((bv[vv]+0.3)*pow(hv[vv],2)/2)+bv[vv]*(hl[vl]-0.05)*(hv[vv]+(hl[vl]-0.05)/2)+ bv[vv]*0.10*(hv[vv]+hl[vl]+0.05);

	ygcv=mec/avc;

    ppvc=ppv+(bv[vv]*0.10*2.5);  // pp viga seção composta (tf/m)



//	 momento inércia seção composta

	ivc=(bv[vv]+0.30)*pow(hv[vv],3)/12+(bv[vv]+0.30)*hv[vv]*pow(((hv[vv]/2)-ygcv),2)+bv[vv]*pow((hl[vl]+0.05),3)/12+bv[vv]*(hl[vl]+0.05)*pow((hv[vv]+((hl[vl]+0.05)/2)-ygcv),2);

//--------------------------------------------------------------------------------------------------------


//	 excentricidades de cada camada (metro)

    	epa=ygv-0.05;
        epb=ygv-0.10;

        epca=ygcv-0.05;
        epcb=ygcv-0.10;

//--------------------------------------------------------------------------------------------------------

//	  módulo resistente

	wvi=iv/ygv;
    wvs=iv/(ygv-(hv[vv]+hl[vl]-0.05));
	wcvi=ivc/ygcv;
    wcvs=ivc/(ygcv-(hv[vv]+hl[vl]+0.05));

//--------------------------------------------------------------------------------------------------------

//	 momentos e tensões (verificação transitória na fase de montagem)

	mvt=(((rl[0]+rl[1])/ll[vl])*2+ppv)*pow(llv,2)/8;	// momento transitório (tf.m)
	                                            // pp e capa + ppviga

	tvi=mvt/(100*wvi);
    tvs=mvt/(100*wvs);   // tensões na seção isolada (mpa)


//	 momentos e tensões verificação transitória somente devido ao peso próprio

	mvpp=(ppv*pow(llv,2))/8;	 // momento devido ao pp da viga	(tf.m)

	tvppi=mvpp/(100*wvi);// tensões devido ao pp da viga	(mpa)

	tvpps=mvpp/(100*wvs);

//--------------------------------------------------------------------------------------------------------
//   tensoes devido ao peso de paredes sobre a viga

//	mvpar=(gpv*(llv**2))/8

//	tvpar=mvpar/(100*wcvi)

//	 momentos e tensões durante vida útil (els)
//
//  com: divide por 1.2 p/ calcular carga por metro na viga
//
//  com: multiplica por 2 p/ considerar a contribuição dos dois lados de lajes
//

//--------------------------------------------------------------------------------------------------------

	mvg=(((rl[2]+rl[3])/ll[vl])*2)*pow(llv,2)/(2*8); // tf.m / pav+rev+paredes na laje

	mvq=(rl[4]/ll[vl])*2*pow(llv,2)/(2*8);   // tf.m / sobre-carga (q)

	tvgi=mvg/(wcvi*100);	// tensões devido pav+rev+par rel. à sç composta(mpa)

	tvq=mvq/(wcvi*100);	// tensões devido à sc (q) rel. à sç composta (mpa)


//	 cálculo momento de cálculo

	mvd=(((1.3*rl[0]+1.4*rl[1]+1.4*(rl[2]/2)+1.4*(rl[3]/2)+1.4*(rl[4]/2))*(2/ll[vl])+1.3*ppv)*pow((llv-lp),2)/8)/100;		// momento de cálculo mn.m

//--------------------------------------------------------------------------------------------------------


//	reações nos pilares

  rpilar=((rl[0]+rl[1]+rl[2]+rl[3]+rl[4])*(2/ll[vl])+ppv)*llv*numpav*1.02;  // [tf]

  //   considera a carga total no pilar + 2% para o pp

  if (rpilar<=380) {
                     sp=0.16;
					 lp=0.4;
                  }
					 else
                     {
					 if (rpilar<=600) {
					                    sp=0.25;
										lp=0.5;
                                        }
										else
										{
										sp=0.36;
										lp=0.6;
                                        }
          }


//--------------------------------------------------------------------------------------------------------


//	  protensão em vigas
//	  protensão na pista (mn)


	pav=-0.97*(na[ana]+nb[anb])*0.0001014*1453;   // mn	(sinal - / compressão)

	soma=(na[ana]*epa+nb[anb]*epb)*0.97*0.0001014*1453*(-1); //(sinal -)

	soma2=(na[ana]*pow(epa,2)+nb[anb]*pow(epb,2))*0.97*0.0001014*1453*(-1);				  //(sinal -)

	sptv=(-1)*((pav/av)+(soma/wvi))+(40.966/pow(fckpm[pm],0.5))*((pav/av)+(soma2/iv));

//	 protensão após trasnferência (mn)

	pat=pav-(na[ana]+nb[anb])*0.0001014*sptv;


	soma3=pat*(float(na[ana])*epa/(float(na[ana])+float(nb[anb])))+ pat*(float(nb[anb])*epb/(float(na[ana])+float(nb[anb])));

	vtinpt=(pat/av)+(soma3/wvi);

	vtsupt=(pat/av)+(soma3/wvs);

//	 protensão em um tempo infinito (mn)

	vpinf=0.8*pav;	  // perda estimada (20%)

	vtinpi=(vpinf/av)+(0.8*soma/wvi);

	vtsupi=(vpinf/av)+(0.8*soma/wvs);

//--------------------------------------------------------------------------------------------------------


//		tensões limites

//	lcj=0.49*fckpm(pm)                 // limite compressão fckj (transitória)
	ltjv=1.5*0.7*0.3*pow((0.7*fckpm[pm]),(2/3)); // limite tração fckj(retangular)

//	lck=0.7*fckpm(pm)                // limite compressão fck   (els)
	ltkv=1.5*0.7*0.3*pow(fckpm[pm],(2/3)); // limite tração fck   (els)




//	   tensões els (mpa)

	descompv=tvi+tvgi+0.3*tvq+vtinpi;
	ffissv=tvi+tvgi+0.4*tvq+vtinpi;

//
//		tensões atuantes nas fases transitórias
//

	tdiv=vtinpt+tvppi;	// desmoldagem inferior
	tdsv=vtsupt+tvpps;	// desmoldagem superior
	ttiv=vtinpt+0.8*tvppi;	// transporte inferior 0.8
	ttsv=vtsupt+0.8*tvpps;	// transporte superior 0.8
	ttiiv=vtinpt+1.3*tvppi;	// transporte inferior 1.3
	ttssv=vtsupt+1.3*tvpps;	// transporte superior 1.3
	tmiv=vtinpi+tvi;			// montagem inferior
	tmsv=vtsupi+tvs;			// montagem superior

//--------------------------------------------------------------------------------------------------------


/////////////////////////////////////////////////////
//
//				  PROTENSÃO SUPERIOR (Considerado apenas na transitória)
//
//////////////////////////////////////////////////////

	if  (ttsv>(2*ltjv))
    {

							pats=0.85*(-0.5716);   // 4 cabos, considerando 85% (mn)
							epcv=ygv-(hv[vv]-0.05);
							epccv=ygcv-(hv[vv]-0.05);
							protsup=(pats/av)+(pats*epcv/wvs);
							ttsv=ttsv+protsup;
       }



	if (tmsv>(2*ltjv))
    {


							pats=0.85*(-0.5716);   // 4 cabos, considerando 85% (mn)
							epcv=ygv-(hv[vv]-0.05);
							epccv=ygcv-(hv[vv]-0.05);
							protsup=(pats/av)+(pats*epcv/wvs);
							tmsv=tmsv+protsup;
       }




	if (tdsv>(2*ltjv))
    {

							pats=0.85*(-0.5716);   // 4 cabos, considerando 85% (mn)
							epcv=ygv-(hv[vv]-0.05);
							epccv=ygcv-(hv[vv]-0.05);
							protsup=(pats/av)+(pats*epcv/wvs);
							tdsv=tdsv+protsup;
     }



//--------------------------------------------------------------------------------------------------------

//	   estado limite último

	ht=hv[vv]+hl[vl]+0.05; //   altura total do pavimento (m)

	da=ht-0.05;
    db=ht-0.10; // braços de alavanca (m)



//	ep=195000 // módulo aço protensão mpa
//	es=210000 // módulo aço mpa

	apa=na[ana]*0.0001014;
    apb=nb[anb]*0.0001014;

	as=npt[anpt]*bp[abp];

//--------------------------------------------------------------------------------------------------------
//
//	  rotina 2006 p cálculo de x (linha-neutra)
//		  cálculo do momento resistente
//

	xv=(1486.9*(apa+apb)+434.8*(as))/(0.4857*fckpm[pm]*bv[vv]);

	za=ht-0.05-0.4*xv;  // braço de alavanca camada a (m)
	zb=za-0.05;		   // braço de alavanca camada b (m)

	mresv=1486.9*(apa*za+apb*zb); // momento resistido pela seção (mn.m)


//////////////////////////////////////////////////////////////
//															//
//				ROTINA FLECHAS VIGAS						//
//															//
//////////////////////////////////////////////////////////////

	cfiv=(pat*epa*llv)/(8*4760*pow(fckpm[pm],0.5)*iv);

	cftv=cfiv*2.5;

	fiv=(3*((rl[0]+rl[1]+rl[2]+rl[3]+0.3*rl[4])*(2/ll[vl])+ppv)*pow(llv,4))/(100*384*4760*pow(fckpm[pm],0.5)*ivc);

	ftv=fiv*2.5;

//--------------------------------------------------------------------------------------------------------

//		 RESTRIÇÃO (Resistente tem q ser superior ao de cálculo)
//		 Estado em Vazio -
//       ZONA INFERIOR - COMPRIMIDA ?

	if (fabs(tdiv)<=lcj)
	                      gv[0]=0;
	                      else
						  gv[0]=fabs(tdiv/lcj)-1;


	if (fabs(ttiv)<=lcj)
	                       gv[1]=0;
	                       else
						   gv[1]=fabs(ttiv/lcj)-1;

	if (fabs(ttiiv)<=lcj)
	                       gv[2]=0;
	                       else
						   gv[2]=fabs(ttiiv/lcj)-1;


	if (fabs(tmiv)<=lcj)
	                       gv[3]=0;
	                       else
						   gv[3]=fabs(tmiv/lcj)-1;


//        zona superior - tracionada ?

//	if (tdsv.le.(2*ltjv)) then 	// limite sugerido jem

	if (tdsv<=pow((0.7*fckpm[pm]),0.5)) 	// limite aci
	                  gv[4]=0;
 	                 else
//					  gv(5)=abs(tdsv/(2*ltjv))-1
					  gv[4]=fabs(tdsv/pow((0.7*fckpm[pm]),0.5))-1;

//	if (ttsv.le.(2*ltjv))     then
	if (ttsv<=(pow(0.7*fckpm[pm],0.5)))
	                      gv[5]=0;
	                      else
						  gv[5]=fabs(ttsv/pow((0.7*fckpm[pm]),0.5))-1;


//	if (ttssv.le.(2*ltjv))     then
 	if (ttssv<=pow((0.7*fckpm[pm]),0.5))
	                       gv[6]=0;
	                       else
						   gv[6]=fabs(ttssv/pow((0.7*fckpm[pm]),0.5))-1;

//	if (tmsv.le.(2*ltjv))    then
	if (tmsv<=pow((0.7*fckpm[pm]),0.5))
	                     gv[7]=0;
	                     else
						 gv[7]=fabs(tmsv/pow((0.7*fckpm[pm]),0.5))-1;


//
//	     els
//

//       descompressao

	if (descompv<=0.05)    // adotado 0.05 como margem e referência
	                     gv[8]=0;
	                     else
						 gv[8]=(descompv/0.05)-1;


//	  FORMACAO DE FISSURA

	if (ffissv<=(2*ltkv)) 			   // limite tração jem
	                      gv[9]=0;			   // els - formação fissura
	                      else
						  gv[9]=(ffissv/(2*ltkv))-1;

//
//		elu e beta x
//

	if (mresv>=(0.98*mvd))
	                    gv[10]=0;					// restrição do momento
	                    else
                        {
						if (mresv<=0)
						                      gv[10]=1-(mresv/(0.98*mvd));
											  else
						                      gv[10]=fabs((0.98*mvd)/mresv)-1;
						}

	bxv=xv/da;

	if (bxv>0)
	                    gv[11]=0;				// beta x viga
	                    else
						gv[11]=fabs(bxv);

    if (bxv<=(1.02*0.6))
	                    gv[12]=0;			   // beta x viga
	                    else
						gv[12]=(bxv/(1.02*0.6))-1;


//	   geometria

    if (na[ana]<=nmax[vv])
	                    gv[13]=0;		   // qde cabos camada
	                    else
						gv[13]=(float(na[ana])/float(nmax[vv]))-1;

	if (nb[anb]<=nmax[vv])
	                    gv[14]=0;		   // qde cabos camada
	                    else
						gv[14]=(float(nb[anb])/float(nmax[vv]))-1;


    if (ht<=hmax)
	                gv[15]=0;			  // altura máxima do pavimento
	                else
					gv[15]=(ht/hmax)-1;


    if (bv[vv]<=bmax)
	                    gv[16]=0;		  // largura máxima viga
	                    else
						gv[16]=((100*bv[vv])/bmax)-1;	//teste: diminuição domínio


	if (llv>=(dminx*(dl)+dminy*(1-dl))) 		// distância mínima entre pilares
	                                      gv[17]=0;
		                                  else
						            gv[17]=((dminx*(dl)+dminy*(1-dl))/llv)-1;



	if (na[ana]>=nb[anb]) 			  // evitar mais ferros na segunda camada(nb(anb))
	              gv[18]=0;		  // em relação à primeira(na)
				  else
				  gv[18]=(float(nb[anb])/float(na[ana]))-1;

//         flechas

	if ((cftv+ftv)<=(1.05*llv/250))
	                               gv[19]=0;
								   else
								   gv[19]=((cftv+ftv)/(1.05*llv/250))-1;


//
//	   somatório penalidades vigas
//
	penv=gv[0]+gv[1]+gv[2]+gv[3]+gv[4]+gv[5]+gv[6]+gv[7]+gv[8]+gv[9]+gv[10]+gv[11]+gv[12]+gv[13]+gv[14]+gv[15]+gv[16]+gv[17]+gv[18]+gv[19];

//--------------------------------------------------------------------------------------------------------

//	   PENALIDADE TOTAL

	pentotal=1+15*(penl+penv);    // intensidade penalização k=10

 //--------------------------------------------------------------------------------------------------------
//
//		  rotina para contar elementos
//
	qdv=nx*(ny+1)*dl+ny*(nx+1)*(1-dl); // qde de vigas pavimento


//	qdv=qdv*numpav                    //qde vigas total


	//QDL=(real(NX)*LLV/1.2)*NY*DL+(real(NY)*LLV/1.2)*NX*(1-DL) ! Qde de lajes PAVIMENTO


// arredonda pra mais porque qualquer coisa vc pode cortar a laje
//if ((nx*llv/1.2)*ny*dl+(ny*llv/1.2)*nx*(1-dl)==int ((nx*llv/1.2)*ny*dl+(ny*llv/1.2)*nx*(1-dl)))
//{
	//qdl=int((nx*llv/1.2)*ny*dl+(ny*llv/1.2)*nx*(1-dl)); // qde de lajes pavimento
	qdl=(float(nx)*llv/ll[vl])*ny*dl+(float(ny)*llv/ll[vl])*nx*(1-dl);
//}
//}
//else
//{
//     qdl=int((nx*llv/1.2)*ny*dl+(ny*llv/1.2)*nx*(1-dl))+1;
//}




//	qdl=qdl*numpav                    // qde lajes total

	qdp=(nx+1)*(ny+1); // qde de pilares

//////////////////////////////////////////////////////////////////////////////
//
//	   cálculo função aptidão
//
//	   comentário: o vão da laje é subtraído da largura da viga
//				   e o da viga do lado do pilar
//
///////////////////////////////////////////////////////////////////////////////

	vpmv=((bv[vv]+0.3)*hv[vv]+bv[vv]*(hl[vl]-0.05))*(llv-lp); // volume vigas
	vpml=a[vl]*(llj-bv[vv]);		                        // volume lajes

	vml=(lx*ly-float(qdp)*sp)*0.05+bv[vv]*0.05*(llv-lp)*qdv; // vol. capa + complemento viga

	vpmp=sp*3.5*1.15;           				 // volume pilar - 01 lance
											 // 1.15 para considerar o console

//   cálculo taxa aço pilar

	if (pm>1) {

	             if (pm==2) {
				              ro=120;
							  if (pm==3)
							                 ro=90;
											 else
											 ro=60;
                             }
				 else
				 ro=150;
              }


//   aço demais elementos

	vapv=(na[ana]+nb[anb])*0.0001014*(llv-lp);    // volume aço protensão viga
	vapl=apl[vl]*(llj-bv[vv]);		         // volume aço protensão laje
	vadv=npt[anpt]*bp[abp]*(llv-lp);               // volume aço doce viga


///////////////////////////////////////////////////////////////////////////////////

//	       custo do concreto das vigas, complemento vigas e lajes

///////////////////////////////////////////////////////////////////////////////////

custoconc=((vpmv*cpm[pm]*qdv)*1.5+(vpml*cpm[pm]*qdl)+(vpmp*cpm[pm]*qdp*1.5))*numpav;

custoconcml=vml*ccml[cml]*1.3*numpav;

// 1.5 pq concreto viga e pilar é mais caro

// em 20/11/06 foi desconsiderado o custo fundação

	/////////////////////////////////
	// custo pilar: REVERRRRRRRRRRRRRRRRRRR
	// x 1.2 pconsiderar fundação!!!!!!!!!!!!!!!!!!!!
	////////////////////////////////

////////////////////////////////////////////////

//     custo despesas operacionais em lajes

///////////////////////////////////////////////

if (vl<28)
              dop=24;
			  else
			  dop=36;         // custos despesas operacionais unitários

cdop=qdl*(llj-bv[vv])*1.2*dop*numpav;       // custos despesas operacionais total


////////////////////////////////

//     CUSTOS TRANSPORTE

////////////////////////////////

if ((llv-lp)>12)
                    ctv=1600;
					else
					ctv=1000;

if ((llj-bv[vv])>12)
                    ctl=1600;
					else
					ctl=1000;


if (numpav>3)
                 ctp=1600;
				 else
				 ctp=1000;


ctt=(((vpmv*qdv*ctv)/10)+((vpml*qdl*ctl)/10)+((vpmp*qdp*ctp)/10))*numpav;


////////////////////////////////////////////

//     CUSTO MONTAGEM					 //

////////////////////////////////////////////

ctmv=ceil((qdv/16)+(qdl/24));   // 1100 guindaste e 400 mo

// ctml=(qdl/24)*1500

ctmp=(qdp/8)*1500;

ctmt=1500*ctmv*numpav+ctmp;





/////////////////////////////////////////////////////////////////////////////////////
//
//	   CUSTOS DAS PERDAS DA PISTA E NÚMERO DE PISTAS UTILIZADAS
//
//	              OBS: ROTINA EM CONSTRUÇÃO	/ falta custo utilizaçao
//										  falta acrescentar na funcao custo
//
/////////////////////////////////////////////////////////////////////////////////////

//lpl=140                     // comprimento pista laje

//nlp=(lpl-mod(lpl,lljc))/lljc  // numero lajes por pista

//qdpl=((qdl-mod(qdl,nlp))/nlp)+1  // qde pistas p confeccionar as lajes

//if (mod(qdl,nlp).eq.0) then
//					   qdpl=qdpl-1
//					   endif

//ptal=((qdpl*lpl)-(qdl*lljc))*apl(vl)*7857 // perda do aço de protensao em kg

//lpv=60						// comprimento pista viga

//nvp=(lpv-mod(lpv,llv))/llv	// numero vigas por pista

//qdpv=((qdv-mod(qdv,nvp))/nvp)+1  // qde de pistas p confeccionar as vigas

//if (mod(qdv,nvp).eq.0) then
//                       qdpv=qdpv-1
//					   endif

//ptav=((qdpv*lpv)-(qdv*llv))*(na(ana)+nb(anb))*0.0001014*7810	// perda aço de prot em kg



//////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////
//
//	                        Custo Aços: PROTENSÃO E PASSIVO
//
//////////////////////////////////////////////////////////////////////

	custoprot=(1.085*vapv*7810.65*qdv+vapl*7857*qdl)*cap*numpav;


	custoad=(vadv*7760*qdv*cad+vpmp*ro*qdp*cad)*numpav;

	custocis=5.6*(((bv[vv]-0.05)+(hv[vv]-0.05))*2+0.12)*bv[vv]*(llv-lp)*qdv*cad*numpav;

	custope=0.86912*(llv-lp)*qdv*numpav*cad;  // custo porta estribo 4 6mm

	custolig=12.125*qdp*numpav*cad;        // custo arm ligação 5 12.5mm (c=2,5 m)

	custoneo=qdp*2*numpav*22.5;   // r$ 22.5

// 1.085 pq cordoalha em viga é mais cara


///////////////////////////////////////////////////////////////////

//	                     CUSTO TOTAL MATERIAIS

///////////////////////////////////////////////////////////////////

	custofab=(custoconc+custoprot+custoad+cdop+custocis+custope)*1.33;

	custotal=(custofab+custoconcml+ctt+ctmt+custoneo+custolig)/numpav;

	float f=0;

	f=custotal*pentotal;

	if(k==0){



    cout <<"      LAJE TT    "<<endl<<endl;

	cout <<" NX:  "<< nx<< endl<<endl;
	cout <<" NY:  "<< ny<< endl<<endl;
	cout <<" DL:   " << dl<< endl<<endl;

	cout <<" FCKCML:   " << fckml[cml]<< endl<<endl;
	cout <<" FCKCPM:   " << fckpm[pm]<< endl<<endl;

	cout <<" HL:   "<< hl[vl]<<endl<<endl;
	cout <<" LLJ:   " << llj<< endl<<endl;
	cout <<" HV:   " << hv[vv]<< endl<<endl;
	cout <<" BV:   "<< bv[vv]<<endl<<endl;
	cout <<" LLV:   " << llv<< endl<<endl;
	cout <<" NA:  "<< na[ana]<< endl<<endl;
	cout <<" NB:  "<< nb[anb]<< endl<<endl;
    cout <<" NPT:  "<< npt[anpt]<< endl<<endl<<endl;


    cout << "somatorio penalidade da laje   :"<<penl<<endl;
    cout << "somatorio penalidade das vigas   :"<< penv<<endl;
	cout << "penalidade total:    "<<pentotal<<endl<<endl;
	cout << "custo concreto:  "<< custoconc <<endl;
	cout << "custo protensao:    "<<custoprot<<endl;
	cout <<"custo transporte:   "<< ctt <<endl;
	cout <<"custo montagem:   "<< ctmt <<endl;
	cout <<"custo despesas operacionais:   "<< cdop <<endl;
	cout << "custo total:    "<<custotal<<endl;
	cout <<"custo aptidao:   "<< f <<endl<<endl;


	 cout <<"--- DADOS DA LAJE INDIVIDUO   1 ---"<<endl;
     cout <<"VL = "<<vl<<endl;
     cout <<"LP = "<<lp<<endl;
	cout <<"contra-flecha total (laje): "<<cft<<endl;
	cout <<"flecha total(laje) : "<<ft<<endl<<endl;


     cout <<"--- DADOS DA VIGA INDIVIDUO   1 ---"<<endl;
     cout<<"VV = "<<vv<<endl;
     cout <<"QDV = "<<qdv<<endl;
     cout <<"QDP = "<<qdp<<endl;
     cout <<"QDL = "<<qdl<<endl;
     cout <<"contra-flecha total (viga): "<< cftv<<endl;
     cout <<"flecha total(viga) :"<<ftv<<endl<<endl;

    for(int b =0; b<17; b++)
    {
        cout<<"GL["<<b<<"] = "<<gl[b]<<endl;
    }
    }
return f;

  }

double transformar (individuo pop[],variavel var[],int n,int l){
		double a,s,b;
		a=0;
		s=0;
		b=0;
		// inicio calcula a posição de inicio da transformação do vetor binário
		for(int j=0;j<n;j++){
			s+=var[j].tamanho;        //"s será a posição de inicio da conta"
		}
		//fim

		//inicio transforma o vetor binário em um numeor natural
		for(int i=int(s);i<(int((s+var[n].tamanho)));i++){
				b=b+(float(pop[l].binario[i]))*pow(2,var[n].tamanho-i+s-1);
			}
		//fim

		//inicio calcula o valor da variável de acordo com os limites e a precisão desejadas
		a+=(var[n].superior-var[n].inferior);
		a=a*b;
		a=a/(pow(2,double(var[n].tamanho))-1);
		a+=var[n].inferior;
		//fim

		//inicio calcula o valor da variável com a prscisão desejada
		a=double((int(a*pow(10,var[n].precisao))));
		a=a/pow(10,var[n].precisao);
		return a;
		//fim
	}


bool gemeos(individuo pop[],int a, int b){
	if(pop[a].natural==pop[b].natural){ //pop.natural como se fosse um dna
		return true;
	}
	else{
		return false;
	}
}


void elitismo1(individuo pop[],individuo npop[],int ptamanho,int elitismo){
	int contador=0;
	contador =elitismo; // garante que o numero de copias seja igual a de elitismo
	int contador2=0;
		//inicio garante que só sejam copiados individuos diferentes
			while(contador>0){
				if(gemeos(pop,contador2+1,contador2)){
					contador2++;
			}
			else{
				npop[elitismo-contador]=pop[contador2];
	             contador--;
	             contador2++;
			}
		//fim
	}
}

int hroleta(individuo pop[],int itamanho){
			  double s=0;
              double u=0;
              double v;
              double r=0;
              double t;
              t=pop[0].aptidao+pop[itamanho-1].aptidao; // valor de referência necessário para a inversão
              for(int i=0;i<itamanho;i++){
            	  s=(t-pop[i].aptidao)+s;
                          }
              v=rand()%100+1; //numero do sortei
              while(u<v-1){
            	  u=((t-pop[int(r)].aptidao)*100)/s+u;
            	  r++;
              }
              return int(r-1);// retorna a posição do individuo sorteado
        }


individuo troca(individuo pop[],int itamanho,int s,int a,int b){
	  individuo aux;
	  aux.binario=new int[itamanho];
	  for(int i=0;i<s;i++){
	          aux.binario[i]=pop[a].binario[i];// preenche o começo do vetor
	  }
	  for(int i=itamanho-1;i>=s;i--){
	  	      aux.binario[i]=pop[b].binario[i]; // preenche o resto do vetor
	  	  }
        return aux;
}


int cruzamento(individuo pop[],individuo npop[],int elitismo,int phroleta,int itamanho,int ptamanho){
	int contador,marcador;
	contador=phroleta/2-1;
	marcador=0;
	 //inicio garante que individuos iguais não sejam cruzados
	 while(contador>0){
		int a,b=0;
		a=hroleta(pop,itamanho);
		b=hroleta(pop,itamanho);
		int s;
		s=rand()%(itamanho-2)+1;
	    npop[elitismo+marcador]=troca(pop,itamanho,s,a,b);
		npop[elitismo+marcador+1]=troca(pop,itamanho,s,b,a);
		marcador+=2;
        contador--;
  }
	 //fim
        return marcador;
}


void preencher(individuo npop[],int ptamanho,int itamanho,int marcador,int elitismo){
	for(int i=(ptamanho-1);i>(marcador+elitismo-1);i--){
		for (int j=0;j<itamanho;j++){
			npop[i].binario[j]=rand()%2;
		}
	}
}


int tamanho(double b ,double c,int p){
	double m, a;

	m=double(int(double(int(c*pow(10,p)))/pow(10,p)-double(int(b*pow(10,p)))/pow(10,p)));

	m=log(m*pow(10,p))/log(2.00);//trasforma na base 2


		a=floor(m);
	if ((m-a)<0.1){
	m=a;}
	else m= a+1;
	return int(m);
}


void ainiciar (individuo pop[],int ptamanho,int itamanho){
	for(int i=0;i<ptamanho;i++){
		for(int j=0;j<itamanho;j++){
			pop[i].binario[j] = rand()%2;
			//pop[i].natural = pop[i].natural+(float(pop[i].binario[j]))*pow(2,itamanho-1-j);
			//cout << pop[i].binario[j] ;
    }
    //cout << "\t" << pop[i].natural << endl;
   }
}


void ordenar(individuo pop[],int ptamanho){
for(int i= ptamanho-1;i>0;i--){
        for(int j=0;j<i;j++){
        	if(pop[j+1].aptidao < pop[j].aptidao){
        			individuo aux;
        			aux = pop[j];
   	     			pop[j] = pop[j+1];
   	     			pop[j+1]=aux;
   	     			}
   	     	 }
   	    }
}


void copiar(individuo npop[],individuo pop[],int ptamanho, int elitismo){
	for(int i=elitismo;i<ptamanho;i++){
		pop[i]=npop[i];
	}
}


void funcaoGrafico(grafico aptidoes[], int ngeracoes){
     char tudo[1000000];
     char temp[30];
     int i;

      for (i=0;i<ngeracoes;i++)
      {

      sprintf(temp,"%5.2f", aptidoes[i].apt);

      strcat(tudo, temp);
      strcat(tudo,",");

     }
     cout<<tudo;

     FILE *p;

      p = fopen("grafico.xls","a");
      if (p==NULL)
      printf("\nErro na abertura ");
      else{

                 fputs(tudo, p);
                 if (ferror(p))
                 printf("\nErro na gravação");
                 else{
                      printf("\nGravação realizada com sucesso");

                      }
           }

      fclose(p);




     }


void evoluir(individuo npop[],individuo pop[],int phroleta,int itamanho,int ptamanho,int elitismo){
	int marcador;
	elitismo1(pop,npop,ptamanho,elitismo);//preenche os primeiros individuos mais aptos
	marcador=cruzamento(pop,npop,elitismo,phroleta,itamanho,ptamanho);//realiza o cruzameto e mostra a proxiam posição
	preencher(npop,ptamanho,itamanho,marcador,elitismo);
    // preenche aleatoriamente o resto da população
}


void unicidade(individuo pop[],int ptamanho,int itamanho, int elitismo){
	for(int i=elitismo;i<ptamanho;i++){
		if(pop[i].aptidao==pop[i+1].aptidao){
			for(int k=0;k<itamanho;k++){
				pop[i].binario[k]=rand()%2;
			}
		}
	}
   ordenar(pop,ptamanho);//garante que a população seja reordenada
}


void mutacao(individuo pop[],int ptamanho,int itamanho,int elitismo, int pmutacao){
	int d=0;
	int p=0;
	double a=0;
	double m=0;

	a = (pmutacao*0,01*ptamanho);
	m  = floor(a);

	for(int i=0;i < m;i++){
		p=rand()%(ptamanho-elitismo-1)+elitismo;
		d=rand()%itamanho;
		if(pop[p].binario[d]==1){
			pop[p].binario[d]=0;
		}
		if(pop[p].binario[d]==0){
			pop[p].binario[d]=1;
		}
	}
}


void menu(void){
	    cout << "******************************************************" << endl;
	    cout << "*            Algoritmo Genetico                      *" << endl;
	    cout << "*                                         versão:1.0 *" << endl;
	    cout << "*      Escolha uma dentre as opcoes abaixo           *" << endl ;
	    cout << "*       [0] Sair                                     *" << endl;
		cout << "*       [1] Entrada de dados                         *" << endl;
		cout << "*       [2] Alterar dados                            *" << endl;
		cout << "*       [3] Otimizar                                 *" << endl;
		cout << "*       [4] Visualizar resultados                    *" << endl;
		cout << "******************************************************" << endl;
}


void smenu2(int ptamanho,int ngeracoes,int elitismo,int phroleta, int pmutacao){
	cout << "Os dados do seu AG estão assim " << endl;
	cout << "O tamannho da populacao e =" << ptamanho << endl;
	cout << "O criterio de parada e o numero de geracoes, sendo =" << ngeracoes<< endl;
	cout << "A porcentagem de elitismo e =" << elitismo << "%"<< endl;
	cout << "A porcentagem para o cruzamento e =" << phroleta << "%"<< endl;
	cout << endl << endl << endl << endl;
	cout << "Escolha o que voce deseja alterar ou sair" << endl;
	cout << "[0] voltar ao menu inicial"<< endl;
	cout << "[1]Tamanho da populacao " << endl;
	cout << "[2]Criterio de parada " << endl;
	cout << "[3]Porcentagem de elitismo" << endl;
	cout << "[4]Tipo de cruzamento" << endl;
	cout << "[5]Porcentagem de mutacao" << endl;
}


int smenu21(int ptamanho){
	int a;
	cout << "O tamannho da populacao e =" << ptamanho << endl;
    cout << "Digite o novo tamanho da populacao :"<< endl;
    cout << "==>  ";
    cin >> a;
    ptamanho=a;
    return ptamanho;
}


int smenu22(int ngeracoes){
	int a;
	cout << "Infelizmente o unico criterio de parada implementado foi o numero de geracoes" << endl;
	cout << "O numero de geracoes e= "<< ngeracoes<< endl;
	cout << "Digite o novo numero de geracoes:" << endl;
	cout << "==>  ";
	cin >> a;
	ngeracoes=a;
	return ngeracoes;
}


int smenu23(int elitismo){
	int a;
	cout << "A porcentagem de elitismo e =" << elitismo << "%"<< endl;
	cout << "Digite a nova porcentagem de elitismo" << endl;
	cout << "==>  ";
	cin >> a;
	elitismo=a;
	return elitismo;
}


int smenu24(int phroleta){
	int a;
	cout << "Infelizmente o unico tipo de cruzamento implementado foi uma variacao da roleta" << endl;
	cout << "A porcentagem e= "<< phroleta<< endl;
	cout << "Digite a nova porcentagem de cruzamento" << endl;
	cout << "==>  ";
	cin >> a;
	phroleta=a;
    return phroleta;
}


int smenu25(int pmutacao){
	int a;

	cout << "A porcentagem de mutacao e= "<< pmutacao<<"%"<< endl;
	cout << "Digite a nova porcentagem de mutacao" << endl;
	cout << "==>  ";
	cin >> a;
	pmutacao=a;
    return pmutacao;
}


int laco(int opcao){
	menu();
	cin >> opcao;
     return opcao;
}


int laco2(int opcao2,int ptamanho,int ngeracoes,int elitismo,int phroleta, int pmutacao){
	smenu2(ptamanho,ngeracoes,elitismo,phroleta,pmutacao);
	cin >> opcao2;
     return opcao2;
}


int main() {

    // Variáveis que serão enviadas para avaliar cada indivíduo;

    float dminx, dminy;  //As distâncias mínimas entre os eixos de pilares
    float lx, ly;        //Dimensões do pavimento em x e y
    float ajx, ajy;
    float hmax;          //Altura max do pavimento
    float  bmax;         //largura max da laje
    float q, gpr, gpl;   //Cargas
    int numind;          // numero de indivíduos
    float mx,my;         // Modulações em X e Y
    int nxmax, nymax;
    int nvv;
    int numgen;
    int k;
    int numpav;          // numero de pavimentos
    float ccml[4];
    float cpm[4];
    float f;

    int TipoLaje;        // Se 0 = alveolar; se 1 = laje TT










    //Custo dos aços
    float cap =7;
    float cad = 4;

    //CUSTO CONCRETO CML


	ccml[0]=147;
	ccml[1]=158;
	ccml[2]=171;
	ccml[3]=185;



     //CUSTO CONCRETO CPM

   cpm[0]=185;
   cpm[1]=200;
   cpm[2]=216;
   cpm[3]=233;

   //    DETERMINAÇÃO TAMANHO DO CROMOSSOMO EM FUNÇÃO MODULAÇÃO MÍNIMA
   //	 FAIXAS DE VÃOS: 1-4 (2BITS) ; 1-8 (3BITS) ; 1-16 (4BITS)
   //	 NXMAX e NYMAX : NÚEROS DE BITS DE NA E NB







	int itamanho=100;                     //valor do maximo tamanho de um individuo referente ao cromossomo
	int ptamanho=1000;                     //tamanho da população
	int pmutacao=30;                      //porcentagem de mutação
	int ngeracoes=5000;                   //numero de gerações
	int elitismo=5;                       //numero de individuos copiados devido ao elitismo
	int phroleta=90;                      //numero de individuos gerados a partir do cruzamento
	int opcao=10;                         //guarda o valor da opção escolhida no menu 1
	int opcao2=10;                        //guarda a opção escolhida nos submenus
	int nvariaveis1;                      //guarda o numero de variaveis
	int num_var;                          //número de variaveis implementadas no bloco de notas
	int num[100];                         //vetor que vai armazenar as variaveis implementadas no bloco de notas
	float penalty[700];                   //vetor que armazena o valor da penalidade dos individuos da população
	char resposta_populacao;              //saber se o usuário deseja que a população será aleatoória ou não
	char resposta_grafico;                //saber se o usuário deseja criar o gráfico das aptidões
	FILE *fp;                             //ponteiro que irá abrir o bloco de notas
	struct individuo pop[1000];            //inicia a população
	struct individuo npop[1000];           //inicia a população que será preenchida com os operadores genéticos
	struct variavel var[1000];             //guardará as caractéristicas das variavéis
	struct grafico aptidoes[ngeracoes];   //vetor que guarda as aptidões dos melhores individuos para formar o gráfico
    srand(time(0));
//inicio entra no laço 0
    while(opcao!=0){
        opcao2=10;
		opcao=laco(opcao);

		if(opcao==1){  //loop para entrada de dado

	    		//Entrada de dados
              	cout << "Entre o numero de pavimentos: "<<endl;
                cin>>numpav;
                cout << "Entre distancia minima pilares X(m): "<<endl;
                cin>>dminx;
	            cout << "Entre distancia minima pilares Y(m): "<<endl;
	            cin>>dminy;
                cout << "Dimensao pavimento X(m): "<<endl;
            	cin>>lx;
                cout << "Dimensao pavimento Y(m): "<<endl;
            	cin>>ly;
                // Altura máxima do pavimento (Laje+Viga+Capa)=HT
	            cout << "Altura maxima pavimento (laje+viga)(m): "<<endl;
	            cin>>hmax;
                //Largura máxima da vig BV(VV)
	            cout << "Largura maxima da viga(m): (.40,.50.. ou .90) "<<endl;
                cin>>bmax;
                cout << "Sobre-Carga (Tf/m2): "<<endl;
                cin>>q;
                cout << "Carga Permanente - PAV+REV (Tf/m2): "<<endl;
                cin>>gpr;
                cout << "Paredes sobre laje (Tf/m2): "<<endl;
                cin>>gpl;
                ajx=lx/dminx;        //ajuste direção x

             	if (ajx>4) {
	                            if (ajx<9)
				                nxmax=3;
								else
								nxmax=4;
              }

				  else
				  nxmax=2;

               	ajy=ly/dminy;		// ajuste direção y

             	if (ajy>4) {
	              if (ajy<9)
				                nymax=3;
								else
								nymax=4;
				  }

				  else
				  nymax=2;



                //   determinação tamanho do cromossomo em função da base viga


               	if (bmax>0.60)
	                  nvv=5;
					  else
					  nvv=4;


                //  tamanho total do cromossomo "numgen"


                numgen=22+nxmax+nymax+nvv;


	    		itamanho=numgen;

	    		cout << itamanho <<endl;

	    }


		if(opcao==2){
	    	while(opcao2!=0){
	    		opcao2=laco2(opcao2,ptamanho,ngeracoes,elitismo,phroleta,pmutacao);
	    		if(opcao2==1){
	    			ptamanho=smenu21(ptamanho);
	    		}
	    		if(opcao2==2){
	    			ngeracoes=smenu22(ngeracoes);
	    		}
	    		if(opcao2==3){
	    			elitismo=smenu23(elitismo);
	    		}
	    		if(opcao2==4){
	    			phroleta=smenu24(phroleta);
	    		}
	    		if(opcao2==5){
	    			pmutacao=smenu25(pmutacao);
	    		}
	    	}
	    //fim
		}
		//inicio gera a população inicial

  if(opcao==3){


            for(int i = 0; i <ptamanho; i++)
            {
	    	               pop[i].binario = new int[itamanho];
	    	               pop[i].objetivo=0;
	    	               pop[i].aptidao=0;
	    	               pop[i].natural=0;
	    	               npop[i].binario = new int [itamanho];
	    	               npop[i].objetivo =0;
	    	               npop[i].natural=0;
	    	               npop[i].aptidao=0;
	    	    }



               ainiciar (pop,ptamanho,itamanho);





	       for (k=0; k<ptamanho; k++)
           {

           TipoLaje = pop[k].binario[22+nxmax+nymax+nvv];

           if (TipoLaje==0)
           pop[k].aptidao=AvaliaIndividuoAlveolar(dminx, dminy,lx, ly, hmax,bmax, q, gpr, gpl, cap, cad,  ptamanho, nxmax, nymax, nvv, numgen,k, numpav, pop);
           else
           pop[k].aptidao=AvaliaIndividuoTT(dminx, dminy,lx, ly, hmax,bmax, q, gpr, gpl, cap, cad,  ptamanho, nxmax, nymax, nvv, numgen,k, numpav, pop);
           }

           for(int i=0;i<ptamanho;i++){
		        for(int j=0;j<itamanho;j++){

			cout << pop[i].binario[j] ;}
            cout << "\t" << pop[i].aptidao << endl;

            }
	    	   ordenar (pop,ptamanho);
	    	   exibir(pop,itamanho,ptamanho);
	    	   cout << "Sua populacao foi iniciada com sucesso!" << endl;


            int contador=0;
	    	int contador2=0;

	    	cout << " \n\n\n\nVoce quer criar um grafico com a função aptidao? Escreva 's' ou 'n' \n"<<endl;
	        cout << "==>  ";
	         cin >> resposta_grafico;

            if(resposta_grafico == 'N' || resposta_grafico == 'n'){

	    	while(contador!=ngeracoes){

	    		cout << "geraçao " << contador+1 << endl;
	    		evoluir(npop,pop,phroleta,itamanho,ptamanho,elitismo);
                copiar(npop,pop,ptamanho,elitismo);
                mutacao(pop,ptamanho,itamanho,elitismo, pmutacao);

	       for (k=0; k<ptamanho; k++)
           {
           TipoLaje = pop[k].binario[21+nxmax+nymax+nvv];

           if (TipoLaje==0)
               pop[k].aptidao=AvaliaIndividuoAlveolar(dminx, dminy,lx, ly, hmax,bmax, q, gpr, gpl, cap, cad,  ptamanho, nxmax, nymax, nvv, numgen,k, numpav, pop);
           else
               pop[k].aptidao=AvaliaIndividuoTT(dminx, dminy,lx, ly, hmax,bmax, q, gpr, gpl, cap, cad,  ptamanho, nxmax, nymax, nvv, numgen,k, numpav, pop);

           }


	    		ordenar(pop,ptamanho);

	    		contador++;
	    		contador2++;
	    		if(contador2==3){

                	unicidade(pop,ptamanho,itamanho,elitismo);
	    			contador2=0;
	    		}
	    		exibir(pop,itamanho,ptamanho);
	    	}
          }



            if(resposta_grafico == 'S' || resposta_grafico == 's'){
	    	while(contador!=ngeracoes){
	    		cout << "geraçao " << contador+1 << endl;

    		    evoluir(npop,pop,phroleta,itamanho,ptamanho,elitismo);
	    		copiar(npop,pop,ptamanho,elitismo);
                mutacao(pop,ptamanho,itamanho,elitismo, pmutacao);


	          for (k=0; k<ptamanho; k++)
             {
                TipoLaje = pop[k].binario[22+nxmax+nymax+nvv];

                if (TipoLaje==0)
                pop[k].aptidao=AvaliaIndividuoAlveolar(dminx, dminy,lx, ly, hmax,bmax, q, gpr, gpl, cap, cad,  ptamanho, nxmax, nymax, nvv, numgen,k, numpav, pop);
                else
                 pop[k].aptidao=AvaliaIndividuoTT(dminx, dminy,lx, ly, hmax,bmax, q, gpr, gpl, cap, cad,  ptamanho, nxmax, nymax, nvv, numgen,k, numpav, pop);
             }

	    		ordenar(pop,ptamanho);

	    		aptidoes[contador].apt=pop[0].aptidao;

	    		contador++;
	    		contador2++;
	    		if(contador2==3){
                    exibir(pop,itamanho,ptamanho);
	    			unicidade(pop,ptamanho,itamanho,elitismo);
	    			contador2=0;
              }
	    		exibir(pop,itamanho,ptamanho);
	    	}
	    	// problema ta agora só na função gráfico
	    	funcaoGrafico(aptidoes,ngeracoes);
	    }
	    //fim
    }
	    //inicio exibe os individuos melhores e piores
	    if(opcao==4){
	    	exibir(pop,itamanho,ptamanho);
	    	double g;
	    	g=0;
	    	cout << "total = " << g << endl;
	    }
	    else{
	    	cout << "ops!" <<endl;
	    }
    }
	return 0;
}


