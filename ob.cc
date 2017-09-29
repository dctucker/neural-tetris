double CTRL[Nout];
void setcontroldata(int pos, int rot){
/*	for(int i=0; i<cmd.length(); i++){
		switch(cmd[i]){
			case '[':
				pos--;
				break;
			case ']':
				pos++;
				break;
			case '\'':
				rot++;
				break;
			case ';':
				rot+=3;
				break;
			break;
		}
		rot%=4;
	}*/
	int i=0;
	
/*	CTRL[i++] = floater(pos <= -4);
	CTRL[i++] = floater(pos == -3);
	CTRL[i++] = floater(pos == -2);
	CTRL[i++] = floater(pos == -1);
	CTRL[i++] = floater(pos == 0);
	CTRL[i++] = floater(pos == 1);
	CTRL[i++] = floater(pos == 2);
	CTRL[i++] = floater(pos == 3);
	CTRL[i++] = floater(pos >= 4);
*/
	rot = (w->curPiece->getRot());
	switch(w->curPiece->getIndex()){
		case 0:
			CTRL[i++]=0.5;
			CTRL[i++]=0.5;
			CTRL[i++]=0.5;
			CTRL[i++]=0.5;
			break;
		case 1:
		case 2:
		case 5:
			CTRL[i++]=floater(rot==1);
			CTRL[i++]=floater(rot==0);
			CTRL[i++]=floater(rot==1);
			CTRL[i++]=floater(rot==0);
			break;
		case 3:
		case 4:
		case 6:
			CTRL[i++] = floater(rot==3);
			CTRL[i++] = floater(rot==2);
			CTRL[i++] = floater(rot==1);
			CTRL[i++] = floater(rot==0);
		break;
	}	
	
}/*
void test5x5(){
	srand(time(NULL));

	double TInput[7][25]; // why use three dimensions when you can do just as much in two?
	for(int j=0; j<7; j++) for(int i=0; i<25; i++)
		TInput[j][i]=0.01; // clear all

	for(int i=0; i<5; i++){ // set up patterns
		TInput[0][(i*5)+2]=0.99;	//1 vertical
		TInput[1][10+i]   =0.99;	//2 horizontal
		TInput[2][i*6]    =0.99;	//3 diagonal back
		TInput[3][i*4]    =0.99;	//4 diagonal fwd
		TInput[4][(i*5)+2]=0.99;	//5 cross +
		TInput[4][10+i]   =0.99;	//5
		TInput[5][i*6]    =0.99;	//6 cross X
		TInput[5][i*4]    =0.99;	//6
	}
	TInput[4][24]=0.01;

	//clear, vert, horiz, bak, fwd
	double TTarget[7][5] = { // solution classification as a fuzzy 5 bit array
		{0.99,0.01,0.01,0.01}, //0:10000 clear
		{0.01,0.99,0.01,0.01}, //1:01000 vertical
		{0.01,0.01,0.99,0.01}, //2:00100 horizontal
		{0.01,0.01,0.01,0.99} //3:00010 diagonal back
//		{0.01,0.01,0.01,0.01,0.99}//, //4:00001 diagonal forward
//		{0.01,0.99,0.99,0.01,0.01}, //5:00011 cross +
//		{0.01,0.01,0.01,0.99,0.99}  //6:00011 cross X
	};
	
	NeuralNet *Nn = new NeuralNet(25,6,4); // 25 inputs -> 7 hidden -> 5 outputs

	char c;
	int v=4;
	for(int e=0;e<40000;e++){
		double TSSE=0;
		for(int i=0; i<4; i++){
			Nn->train(TInput[i],TTarget[i]);
			TSSE += Nn->tsse();
		}
		if(e%v==0){
			std::cout << e << "\t" << sqrt(TSSE/35) << "\n";
			for(int i=0; i<7; i++){
				if(i<4) Nn->test(TInput[i],TTarget[i]);
				Nn->printO();
			}
			if(TSSE<0.7) v*=2;
		}
	}
}*/

