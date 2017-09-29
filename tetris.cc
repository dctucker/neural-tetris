#include <iostream>
#include <string>
#include <math.h>
#include <time.h>
#include <stdlib.h>
#define rho ((double )(((double )rand())/((double )RAND_MAX)))
#define LO 0.001
#define HI 0.99999
#define floater(x) (((x))?HI:LO); 
#include "neural.cc"
using namespace std;

unsigned char blks[7][4][4][4]={ // 7 blocks, 4 rotations, 4x4 grid each 
			{{{0,0,0,0},{0,0,0,0},{1,1,0,0},{1,1,0,0}}, // O
			{{0,0,0,0},{0,0,0,0},{1,1,0,0},{1,1,0,0}},  // O
			{{0,0,0,0},{0,0,0,0},{1,1,0,0},{1,1,0,0}},  // O
			{{0,0,0,0},{0,0,0,0},{1,1,0,0},{1,1,0,0}}}, // O

			{{{0,0,0,0},{1,1,1,1},{0,0,0,0},{0,0,0,0}}, // ----
			{{0,1,0,0},{0,1,0,0},{0,1,0,0},{0,1,0,0}},  // |
			{{0,0,0,0},{1,1,1,1},{0,0,0,0},{0,0,0,0}},  // ----
			{{0,1,0,0},{0,1,0,0},{0,1,0,0},{0,1,0,0}}}, // |

			{{{0,0,0,0},{0,1,0,0},{1,1,0,0},{1,0,0,0}}, // Z
			{{0,0,0,0},{1,1,0,0},{0,1,1,0},{0,0,0,0}},  // ':.
			{{0,0,0,0},{0,1,0,0},{1,1,0,0},{1,0,0,0}},  // Z
			{{0,0,0,0},{1,1,0,0},{0,1,1,0},{0,0,0,0}}}, // ':.

			{{{0,0,0,0},{0,1,0,0},{1,1,0,0},{0,1,0,0}}, // -|
			{{0,0,0,0},{0,1,0,0},{1,1,1,0},{0,0,0,0}},  // .L
			{{0,0,0,0},{1,0,0,0},{1,1,0,0},{1,0,0,0}},  // |-
			{{0,0,0,0},{1,1,1,0},{0,1,0,0},{0,0,0,0}}}, // T

			{{{0,0,0,0},{1,1,1,0},{1,0,0,0},{0,0,0,0}}, // :--
			{{0,0,0,0},{1,1,0,0},{0,1,0,0},{0,1,0,0}},  // '|
			{{0,0,0,0},{0,0,1,0},{1,1,1,0},{0,0,0,0}},  // --'
			{{0,0,0,0},{1,0,0,0},{1,0,0,0},{1,1,0,0}}}, // L

			{{{0,0,0,0},{1,0,0,0},{1,1,0,0},{0,1,0,0}}, // S
			{{0,0,0,0},{0,1,1,0},{1,1,0,0},{0,0,0,0}},  // .:-
			{{0,0,0,0},{1,0,0,0},{1,1,0,0},{0,1,0,0}},  // S
			{{0,0,0,0},{0,1,1,0},{1,1,0,0},{0,0,0,0}}}, // .:-

			{{{0,0,0,0},{1,1,0,0},{1,0,0,0},{1,0,0,0}}, // |'
			{{0,0,0,0},{1,1,1,0},{0,0,1,0},{0,0,0,0}},  // --:
			{{0,0,0,0},{0,1,0,0},{0,1,0,0},{1,1,0,0}},  // J
			{{0,0,0,0},{1,0,0,0},{1,1,1,0},{0,0,0,0}}}  // '--
		};
unsigned char skrt[7][4][4]={
	{{1,1,0,0},{1,1,0,0},{1,1,0,0},{1,1,0,0}},// 0
	{{1,1,1,1},{0,1,0,0},{1,1,1,1},{0,1,0,0}},// 1
	{{1,2,0,0},{2,1,1,0},{1,2,0,0},{2,1,1,0}},// 2
	{{2,1,0,0},{1,1,1,0},{1,2,0,0},{2,1,2,0}},// 3
	{{1,2,2,0},{3,1,0,0},{1,1,1,0},{1,1,0,0}},// 4
	{{2,1,0,0},{1,1,2,0},{2,1,0,0},{1,1,2,0}},// 5
	{{1,3,0,0},{2,2,1,0},{1,1,0,0},{1,1,1,0}} // 6
};

class Piece{
  private:
	int P,R; // type, rotation
	unsigned char blocks[4][4];
  public:
	int xpos,ypos,ypos1;
  public:
	Piece(int p=(int)(rho*7)){
		getNew(p);
	}
	void getNew(int p=(int)(rho*7)){
		P=p;
		R=0;
		initBlocks();
		ypos=ypos1=0;
		xpos=4;
	}
	void initBlocks(){
		for(int i=0; i<4; i++){
			for(int j=0; j<4; j++){
				blocks[i][j]=blks[P][R][i][j];
			}
		}
	}
	int getIndex(){
		return P;
	}
	unsigned char grid(int i, int j){
		if((i<4 && j<4) && (i>=0 && j>=0))
		return blocks[i][j]; else return 0;
	}
	void rotate(int r=1){ //std::cerr << "rotate()";
		if(r<0) r=3;
		R+=r; R%=4;
		initBlocks();
	}
	int getRot(){
		switch(P){
			case 0:
				return 0;
				break;
			case 1:
			case 2:
			case 5:
				return R%2;
				break;
			case 3:
			case 4:
			case 6:
				return R;
			default:
				return -1;
		}
	}
	int numRots(){
		switch(P){
			case 0:
				return 1;
			case 1:
			case 2:
			case 5:
				return 2;
			case 3:
			case 4:
			case 6:
				return 4;
			default: return -1;
		}
	}
	void print(){
		for(int i=0; i<4; i++){
			for(int j=0; j<4; j++){
				std::cout << ((blocks[i][j]==1)?"O":" ");
			}
			std::cout <<"\n";
		}
	}
	unsigned char skirt(int i){
		return skrt[P][R][i];
	}
	unsigned char skirts(int i){
		return skrt[P][i/4][i%4];
	}
};

#define NV 20
#define NH 10

class Well{
  public:
	unsigned char well[NV][NH];
	int shelf[2];
	int lines;
	double R[100];
  public:
	Piece *curPiece;
  public:
	Well(){
		clearWell();
		curPiece = new Piece();
	}
	~Well(){
		delete curPiece;
	}
	void clearWell(){
		for(int i=0; i<NV; i++){
			for(int j=0; j<NH; j++){
				well[i][j]=0;
			}//j
		}//i
	}
	void printWell(){
		int x=0,y=0;
		for(int i=0; i<NV; i++){
			std::cout << "|";
			for(int j=0; j<NH; j++){
				if(curPiece->grid(i-curPiece->ypos,j-curPiece->xpos)==1)
					std::cout << "0";
				else if(well[i][j]==1)
					std::cout << "O";
				else std::cout <<" ";
			}
			std::cout << "|\n";
		}
		std::cout << "+----------+\n";
	}
	void newPiece(){
		curPiece->getNew();
	}
	bool moveLeft(){ //std::cerr << "moveLeft()\n";
		if(isValid(curPiece->ypos,curPiece->xpos-1))
			curPiece->xpos--;
		else return false;
		return true;
	}
	bool moveRight(){ //std::cerr << "moveRight()\n";
		if(isValid(curPiece->ypos,curPiece->xpos+1))
			curPiece->xpos++;
		else return false;
		return true;
	}
	bool moveDown(){ //std::cerr << "moveDown()\n";
		if(isValid(curPiece->ypos+1,curPiece->xpos))
			curPiece->ypos++;
		else return false;
		return true;
	}
	bool rotateLeft(){ //std::cerr << "rotateLeft()\n";
		curPiece->rotate(-1);
		if(!isValid(curPiece->ypos,curPiece->xpos)){
			if(isValid(curPiece->ypos,curPiece->xpos-1))
				curPiece->xpos--;
			else if(isValid(curPiece->ypos,curPiece->xpos+1))
				curPiece->xpos++;
			else {
				if(isValid(curPiece->ypos,curPiece->xpos-2)){
					curPiece->xpos-=2;
				} else {
					curPiece->rotate(1);
					return false;
				}
			}
		}
		return true;
	}
	bool rotateRight(){
		curPiece->rotate(1);
		if(!isValid(curPiece->ypos,curPiece->xpos)){
			if(isValid(curPiece->ypos,curPiece->xpos-1))
				curPiece->xpos--;
			else if(isValid(curPiece->ypos,curPiece->xpos+1))
				curPiece->xpos++;
			else {
				if(isValid(curPiece->ypos,curPiece->xpos-2)){
					curPiece->xpos-=2;
				}else{
					curPiece->rotate(-1);
					return false;
				}
			}
		}
		return true;
	}
	unsigned char pos(int i,int j){
		if(j<NH && i<NV && j>=0 && i>=0)
			return well[i][j];
		else return 1;
	}
	bool isValid(int i1, int j1){ //std::cerr << "isValid()\n";
		for(int i=0; i<4; i++){
			for(int j=0; j<4; j++){
				if((curPiece->grid(i,j)+pos(i+i1,j+j1)) >1)
					return false;
			}
		}
		return true;
	}
	int checkLines(bool hypothetical=false){ //std::cerr << "checklines()\n";
		int l=0;
		for(int i=0; i<NV; i++){
			int s=0;
			for(int j=0; j<NH; j++){
				s+=well[i][j];
			}
			if(s==NH){
				l++;
				if(!hypothetical){
					for(int i1=i; i1>0; i1--){
						for(int j1=0; j1<NH; j1++){
							well[i1][j1]=well[i1-1][j1];
						}
					}
				}
			}
		}
		return l;
	}
	void drop(bool hypothetical=false){
		int ypos=curPiece->ypos;
		while(ypos<NV){
			if(isValid(ypos,curPiece->xpos)) ypos++; else break;
		}
		--ypos;
		for(int i=0; i<4; i++){
			for(int j=0; j<4; j++){
				if(pos(i+ypos,j+curPiece->xpos)==0) 
					well[i+ypos][j+curPiece->xpos]=curPiece->grid(i,j);
			}
		}
		curPiece->ypos1=ypos;
		if(!hypothetical){
			checkLines();
			newPiece();
		}
	}
	int testDrop(bool undrop1=true){
		int ypos=curPiece->ypos, L;
		while(ypos<NV){
			if(isValid(ypos,curPiece->xpos)) ypos++; else break;
		}
		--ypos;
		for(int i=0; i<4; i++){
			for(int j=0; j<4; j++){
				if(pos(i+ypos,j+curPiece->xpos)==0) 
					well[i+ypos][j+curPiece->xpos]=curPiece->grid(i,j);
			}
		}
		curPiece->ypos1=ypos;
		//count lines
		L=checkLines(true);
		//std::cout << L;
		if(undrop1){
			for(int i=0; i<4; i++){ // undo
				for(int j=0; j<4; j++){
					if(curPiece->grid(i,j)==1)
						well[i+curPiece->ypos1][j+curPiece->xpos]=0;
				}
			}
		}
		//if(undrop1) unDrop();
		return L;
	}
	double getFill(){
		double s=0,v=0;
		testDrop(false);
		
		for(int i=0; i<4; i++){
			int n=0;
			for(int j=0; j<4; j++){
				if(curPiece->grid(i,j)==1) n++; // sum vertical space
			}
			if(n>0){
				v++;
				for(int j=0; j<NH; j++){ // sum horizontal fill
					if(pos(i+curPiece->ypos1,j)==1) s++;
				}
			}
		}
		for(int i=0; i<4; i++){ // undo
			for(int j=0; j<4; j++){
				if(curPiece->grid(i,j)==1)
					well[i+curPiece->ypos1][j+curPiece->xpos]=0;
			}
		}
		return s / (v*NH);

	}
	double getVFill(){
		double s=0, h=0;
		testDrop(false);

		for(int j=0; j<4; j++){
			int n=0;
			if(curPiece->skirt(j)>0){
				h++;
				for(int i=0; i<NV; i++){
					if(pos(i,curPiece->xpos+j)==1) s++;
				}
			}
		}
		for(int i=0; i<4; i++){ // undo
			for(int j=0; j<4; j++){
				if(curPiece->grid(i,j)==1)
					well[i+curPiece->ypos1][j+curPiece->xpos]=0;
			}
		}
		return s / (h*NV);
	}
	int *getShelf(){
		bool haveL=false, haveR=false,ts=false;
		int l,r;
		testDrop(false);
		for(int j=0; j<4; j++){
			if(!ts && curPiece->skirt(j)>0){ // find left
				l = pants(j+curPiece->xpos-1);
				if(l==-1) l=0;
				else l -= pants(j+curPiece->xpos);
				if(l>0) l=0;
				l=-l;
				haveL=true;
				ts=true;
			}
			if(ts && curPiece->skirt(j)==0){ // find right
				if(!haveR){
					r = pants(j+curPiece->xpos);
					if(r==-1) r=0;
					else r -= pants(j+curPiece->xpos-1);
					if(r>0) r=0;
					r=-r;
					haveR=true;
				}
			}
			if(haveR) break;
		}
		if(!haveR){
			r=pants(4+curPiece->xpos);
			if(r==-1) r=0;
			else r -= pants(3+curPiece->xpos);
			if(r>0) r=0;
			r=-r;
			haveR=true;
		}
		unDrop();
		shelf[0]=l;
		shelf[1]=r;
		return shelf;
	}
	int numGaps(){
		int s=0;
		bool solid;
		testDrop(false);
		for(int j=0; j<4; j++){
			if((curPiece->skirt(j) > 0) && (j+curPiece->xpos < NH)){
				solid=false;
				for(int i=0; i<NV; i++){
					if(pos(i,j+curPiece->xpos)!=0) solid=true;
					if(solid && pos(i,j+curPiece->xpos)==0) s++;
				}
			}
		}
		unDrop();
		return s;
	}
	inline void unDrop(){
		for(int i=0; i<4; i++){ // undo
			for(int j=0; j<4; j++){
				if(curPiece->grid(i,j)==1)
					well[i+curPiece->ypos1][j+curPiece->xpos]=0;
			}
		}
	}
	double *getneural(){
		int peak[NH];
		for(int i=0; i<100; i++) R[i]=LO;
		for(int i=0; i<NV; i++){
			for(int j=0; j<NH; j++){
				if(peak[j]==0 && pos(i,j)==1) peak[j]=i;
			}
		}
/*		for(int i=0; i<NH; i++){
			if(i >= curPiece->xpos && i <= curPiece->xpos+3){
				unsigned char c=curPiece->skirt(i);
				R[2*i+0]=floater(c & 2);
				R[2*i+1]=floater(c & 1);
			}
			else {
				R[2*i]=LO;
				R[2*i+1]=LO;
			}
//			std::cout << R[i];
		}*/
		for(int i=0; i<4; i++){
			for(int j=0; j<4; j++){
				unsigned char c=curPiece->skirts(4*i+j);
				R[8*i+j+0]=floater(c & 2);
				R[8*i+j+1]=floater(c & 1);
			}
		}
		for(int i=0; i<NH; i++){
			R[32+4*i]=floater(peak[i] & 1);
			R[32+4*i+1]=floater(peak[i] & 2);
			R[32+4*i+2]=floater(peak[i] & 4);
			R[32+4*i+3]=floater(peak[i] & 8);
		}
//		char c;
//		cin >> c;
		return R;	
	}
	int pants(int i){
		if(i>=NH || i<0) return -1;
		int r[NH];
		int max;
		for(int j=0; j<NH; j++){
			int v=0;
			while(well[v++][j]==0 && v<=NV);
			r[j]=v;
			if(max<v) max=v;
		}
		for(int j=0; j<NH; j++){
			r[j]=max-r[j];
		}
		return r[i];
	}
	
} *w;

void quit(NeuralNet *nn=0){
	delete w;
	delete nn;
	exit(0);
}

#define Nout 4 
int land[4];
int sumGapFit(){ // determines how well a piece fits
	int a=0;
	int b=0;
	int gaps=0;
	for(int i=0; i<4; i++){
		a=w->pants(i+w->curPiece->xpos);
		b=w->curPiece->skirt(i)-1;
		if(b>-1) {
			//std::cout << a-b;
			land[i]=a-b;
		}
		else{
			//std::cout << ".";
			land[i]=64;
		}
		//std::cout << "\t";
	}
	for(int i=1; i<4; i++){
		if(land[i] !=64 && land[i-1] !=64)
		gaps+=abs(land[i]-land[i-1]);
	}
	//std::cout << "\n";
	return gaps;
}
double healthFit(int g){ // piece fit to real (0,1)
	if(g==0) return HI;
	else return HI / (((int)abs(g)) + 2.0);
}
double healthLines(int g){
	if(g==0) return 0.01;
	else return 0.24999*(double)(g);
}
double healthFill(double s){
	if(s<=0) return LO;
	if(s>=1) return HI;
	else return s;
}
double healthVFill(double s){
	s=1-s;
	if(s<=0) return LO;
	else if(s>=1) return HI;
	else return s;
}
double healthGaps(int s){
	if(s>(NV/2)) return 0.01;
	else return 0.99 - 0.1*(double)s;
}
double healthShelf(int s){
	double r=0.99 - 0.1*(double)s;
	if(r>0) return r;
	else return HI;
}

double HF,HL,HG,HH,HV,SL,SR;
double HFA[40],HLA[40],HGA[40],HHA[40],HVA[40],SLA[40],SRA[40];
double moveHealth(){
	int *sh;
	HF=healthFit(sumGapFit()),
	HL=healthLines(w->testDrop()),
	HG=healthGaps(w->numGaps()),
	HH=healthFill(w->getFill());
	HV=healthVFill(w->getVFill());
	
	sh=w->getShelf();
	SL=healthShelf(sh[0]);
	SR=healthShelf(sh[1]);

/*	std::cout.precision(5);
	std::cout <<HF <<"\t"<< HL <<"\t"<< 
				HG <<"\t"<< HH <<"\t"<<
				HV <<"\t"<< SL <<","<< SR 
			  << "\n";
*/
	return ((HF+HL+HG+HH+HV+(SL+SR)/10)/ 5.2); // bounded between (0,1)
}
double MoveMatrix[40];
double HNeural[7];
double *moveNeural(){
/*	for(int i=0; i<4; i++){
		for(int j=0; j<4; j++){
			HNeural[i*4+j]=w->curPiece->grid(i,j);
		}
	}*/
//	for(int i=0; i<40; i++){
//		HNeural[i]=MoveMatrix[i];
//	}
	HNeural[0]=HF;
	HNeural[1]=HL;
	HNeural[2]=HG;
	HNeural[3]=HH;
	HNeural[4]=HV;
	HNeural[5]=SL;
	HNeural[6]=SR;
	return HNeural;
}

int considerMoves(){ // find best move, position piece
	double moves[4], r=0,r2=0;
	int pos,pos2,rot2,index;
//	cout << "considerMoves()\n";
	for(int rot=0; rot<4; rot++){
		for(int i=0; i<NH; i++){ // all the way left
			w->moveLeft();
		}
		pos=0;
		while(pos<NH){
			index=rot*NH+pos;
			r=moveHealth();
			MoveMatrix[index]=r;
			HFA[index]=HF;
			HLA[index]=HL;
			HGA[index]=HG;
			HHA[index]=HH;
			HVA[index]=HV;
			SLA[index]=SL;
			SRA[index]=SR;
			if(r>r2) { // determine the winner
				r2=r;
				pos2=pos;
				rot2=rot;
			}
			w->moveRight();
			pos++;
		}
		w->rotateRight();
	}
	for(int i=0; i<rot2; i++){ // rotate to best
		w->rotateRight();
	}
	for(int i=0; i<NH; i++){ // all the way left
		w->moveLeft();
	}
	pos=0;
	while(pos2-->0){ // move right to best
		w->moveRight();
		pos++;
	}
	return pos;
}
int considerNeural(NeuralNet *nn){
	double moves[4], r=0, r2=0;
	int pos,pos2,rot2,index;
//	cout << "considerNeural()\n";
	for(int rot=0; rot<4; rot++){
		for(int i=0; i<NH; i++){
			w->moveLeft();
		}
		pos=0;
		while(pos<NH){
			index=rot*NH+pos;
			moveHealth();
			nn->test(moveNeural());
			r=nn->getOutput(0);
			if(r>r2){
				r2=r;
				pos2=pos;
				rot2=rot;
			}
			w->moveRight();
			pos++;
		}
		w->rotateRight();
	}
	for(int i=0; i<rot2; i++)
		w->rotateRight();
	for(int i=0; i<NH; i++)
		w->moveLeft();
	pos=0;
	while(pos2-->0){
		w->moveRight();
		pos++;
	}
	return pos;
}
int main(int argc, char *argv[]){
//	test5x5();
	int pos=0, rot=0, pos2, NP=0, moves=0,TNP=0;
	double tsse=0,rmse=0;
	double in[5];
	char c;
	bool clear,neural=false;
	if(argc>1){
		std::cout << "\nKeys:" <<
			"\n c  consider moves" <<
			"\n C  auto move     " <<
			"\n [  move left     " <<
			"\n ]  move right    " <<
			"\n ;  rotate left   " <<
			"\n \'  rotate right " <<
			"\n /  drop          " <<
			"\n q  quit\n";
		exit(0);
	} 
	srand(time(NULL));
	w = new Well();
	NeuralNet *nn = new NeuralNet(7,10,1);

	pos=considerMoves();
	rot=w->curPiece->getRot();
	w->printWell();

	for(int Q=0;Q<10000; Q++){
		clear=true;
		std::cin >> c;
//		c='/';
		switch(c){
			case 'c':
				pos=considerMoves();
				rot=w->curPiece->getRot();
				break;
			case 'C':
				neural=false;
				break;
			case 'x':
				pos=considerNeural(nn);
				rot=w->curPiece->getRot();
				break;
			case 'X':
				neural=true;
				break;
			case '[': // left
				if(w->moveLeft()) pos--;
				break;
			case ']': // right
				if(w->moveRight()) pos++;
				break;
			case '.': // down
				w->moveDown();
				break;
			case '\'': // rotl
				if(w->rotateLeft()){
					rot=w->curPiece->getRot();
				}
				break;
			case ';': // rotr
				if(w->rotateRight()){
					rot=w->curPiece->getRot();
				}
				break;
			case '-':
				//pos2=w->curPiece->xpos;
				//nn->train(moveNeural(),LO);
				MoveMatrix[NH*rot+pos] -= 0.1;
				break;
			case '+':
				//pos2=w->curPiece->xpos;
				//nn->train(moveNeural(),HI);
				MoveMatrix[NH*rot+pos] += 0.1;
				break;
			case '/': // train
//				cout << "Training... inputs and target follow.\n";
				moves++;
				for(int i=0; i<w->curPiece->numRots()*NH; i++){
					if( i>0 && (
						in[0] != HFA[i-1] ||
						in[1] != HLA[i-1] ||
						in[2] != HGA[i-1] ||
						in[3] != HHA[i-1] ||
						in[4] != HVA[i-1] ||
						in[5] != SLA[i-1] ||
						in[6] != SRA[i-1] ||
						MoveMatrix[i]!=MoveMatrix[i-1]	
					  ) ){
						NP++;
						in[0] = HFA[i];
						in[1] = HLA[i];
						in[2] = HGA[i];
						in[3] = HHA[i];
						in[4] = HVA[i];
						in[5] = SLA[i];
						in[6] = SRA[i];
						if(i == NH*rot+pos) MoveMatrix[i]=HI;
						nn->train(in,MoveMatrix[i]);
/*						cout << in[0] <<"\t"<< in[1] <<"\t"<<
								in[2] <<"\t"<< in[3] <<"\t"<<
								in[4] <<"\t"<< in[5] <<"\t"<< 
								in[6] <<"\t"<< MoveMatrix[i]
							 << "\n";*/
						tsse+=nn->tsse();
					}
				}
				rmse=sqrt(tsse/(double)NP);
				//TNP+=NP;
				w->drop();
				pos=considerMoves();
				if(neural){
					pos=considerNeural(nn);
				}
				rot=w->curPiece->getRot();
				break;
			case '?': // drop
				//std::cout << w->testDrop();
				//clear=false;
				w->drop();
				break;
			case 'q': quit();
				break;
		}

//		if(clear){ std::cout<<'\x1b'<<"[2J"<<std::flush;}
		w->printWell();
//		std::cout <<"Fits"<<"\t"<<"Lines"<<"\t"<<
//					"-Gaps"<<"\t"<<"Fill"<<"\t"<<"VFill"<<"\t"<<"Shelf L,R"<<"\n";
//		cout <<"Sum:    " << moveHealth() << "\n";
		cout << NP << "\t" << rmse << "\n";
/*		

		nn->target[0]=MoveMatrix[NH*rot+pos];
		nn->test(moveNeural());
		cout <<"Target: ";
		nn->printT();
		cout <<"Output: ";
		nn->printO();
		cout <<"P,R: "<< pos << "," << rot << "\t";
		if(neural) cout << "output mode\n";
		else cout << "target mode\n";*/
	}// */
}

