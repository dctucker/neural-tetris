#define WeightI(i,j) weightIn[i*Ninputs+j]
#define WeightO(i,j) weightOut[i*Nhidden+j]

class NeuralNet {
	private:
		float	*output, *hidden,
			   *weightIn,*weightOut,
			   *biasHid,*biasOut,
			   *errorHid, *errorOut;
		int Ninputs,Nhidden,Noutputs;
	public:
		float  *input,*target;
		float  bias, eta,RMSE;
	private:
		float  sigmoid(float  x){
			return 1.0F / ( 1.0F + exp(-x) );
		}
		void initWeights(){
			for(int i=0; i<Ninputs; i++){
				for(int j=0; j<Nhidden; j++){
//					std::cout << (i*Ninputs+j)<<"\n";
					WeightI(i,j)=sigmoid(rho);
					std::cout << WeightI(i,j);
				}
			}
			char c;
			std::cin >> c;
			for(int i=0; i<Nhidden; i++){
				biasHid[i]=0.0F;
				for(int j=0; j<Noutputs;j++){
					WeightO(i,j)=sigmoid(rho);
					if(i==0) biasOut[j]=0.0F;
				}
			}
		}
	public:
		NeuralNet(int ni,int nh,int no){
			bias=1.0F;
			eta=1.9F;
			
			Ninputs=ni;
			Nhidden=nh;
			Noutputs=no;
			
			input = new float [Ninputs];
			target= new float [Noutputs];
			
			hidden= new float [Nhidden];
			output= new float [Noutputs];
			
			weightIn= new float [Ninputs*Nhidden];
			weightOut=new float [Nhidden*Noutputs];
			
			biasHid=  new float [Nhidden];
			biasOut=  new float [Noutputs];

			errorHid= new float [Nhidden];
			errorOut= new float [Noutputs];
			
			initWeights();
		}
		void print(bool header=false){
			std::cout.precision(4);
			if(header) std::cout << "In:\n";
			for(int i=0; i<Ninputs; i++){
				std::cout << input[i] << "\t";
				for(int j=0; j<Nhidden; j++)
					std::cout << WeightI(i,j) << "\t";
				std::cout << "\n";
			}
			if(header) std::cout << "Hid:";
			for(int i=0; i<Nhidden; i++){
				std::cout << "\t" << hidden[i];
			}
			std::cout << "\n\n";
			if(header) std::cout << "Hid:\n";
			for(int i=0; i<Nhidden; i++){
				std::cout << hidden[i] << "\t";
				for(int j=0; j<Noutputs; j++){
					std::cout << WeightO(i,j) << "\t";
				}
				std::cout << "\n";
			}
			if(header) std::cout << "Out:";
			for(int i=0; i<Noutputs; i++){
				std::cout << "\t" << output[i];
			}
			std::cout << "\nTarget:";
			for(int i=0; i<Noutputs; i++){
				std::cout << "\t" << target[i];
			}
			std::cout << "\n\n";
		}
		void printIO(){
			for(int i=0; i<Ninputs; i++){
				std::cout << input[i] << " ";
			}
			std::cout << ": ";
			for(int i=0; i<Noutputs; i++){
				std::cout << target[i] << " ";
			}
			std::cout << " -> ";
			for(int i=0; i<Noutputs; i++){
				std::cout << ((output[i]<0.5) ? "0.1 " : "0.9 ");
			}
			std::cout << " (";
			for(int i=0; i<Noutputs; i++){
				std::cout << output[i] << " ";
			}
			std::cout << ")\n";
		}
		void printO(){
			std::cout.precision(4);
			for(int k=0; k<Noutputs; k++)
				//std::cout << ((output[k]>0.7)?":":".") << (int)(output[k]*10)
				//   << ((int)(output[k]*100)%10) << " ";
				std::cout << output[k];
			std::cout << "\n";
		}
		void calculate(){
			float  netj;
			for(int j=0; j<Nhidden; j++){
				float  s=0;
				for(int i=0; i<Ninputs; i++){
					s+=input[i]*WeightI(i,j);
				}
				netj=bias*biasHid[j]+s;
				hidden[j]=sigmoid(netj);
			}
			for(int k=0; k<Noutputs; k++){
				float  s=0;
				for(int j=0; j<Nhidden; j++){
					s+=hidden[j]*WeightO(j,k);
				}
				netj=bias*biasOut[k]+s;
				output[k]=sigmoid(netj);
			}
		}
		void updateErrors(){
			//calculate error at outputs
			for(int k=0; k<Noutputs; k++){
				errorOut[k] =
					(target[k]-output[k]) * output[k] * (1-output[k]);
			}
			
			//use output error to compute error for hidden
			for(int j=0; j<Nhidden; j++){
				float  s=0;
				for(int k=0; k<Noutputs; k++){
					s+=errorOut[k]*WeightO(j,k);
				}
				errorHid[j] = hidden[j]*(1-hidden[j])*s;
			}
		}
		void updateW(){
			//use hidden error to compute weight adjustments
			for(int k=0; k<Noutputs; k++){
				for(int j=0; j<Nhidden; j++){
					WeightO(j,k)+=eta*errorOut[k]*hidden[j];
				}
			}
			for(int j=0; j<Nhidden; j++){
				for(int i=0; i<Ninputs; i++){
					WeightI(i,j)+=eta*errorHid[j]*input[i];
				}
			}
		}
		void train(float  *in, float  *tar){
			//apply inputs
			std::cout << "I=";
			for(int i=0; i<Ninputs; i++){
				input[i]=in[i];
				std::cout << (input[i]>0.5)?"1":"0";
			}
				std::cout << "\nT=";
			for(int i=0; i<Noutputs; i++){
				target[i]=tar[i];
				std::cout << (target[i]>0.5)?"1":"0";
			}
			
			std::cout << "\nO=";
			calculate();
			for(int i=0; i<Noutputs; i++){
				std::cout << output[i]<<
					" ";
			}
			std::cout << "\n";
			updateErrors();
			updateW();
//			TSSE+=tsse();
			char c; std::cin>>c;
		}
		void train(unsigned char m[20][10],float  *tar){
			for(int i=0; i<Ninputs; i++){
				input[i]=(m[i/10][i%10]==1)?0.999:0.001;
			}
			for(int k=0; k<Noutputs; k++){
				target[k]=tar[k];
			}
			calculate();
			updateErrors();
			updateW();
		}
		void test(unsigned char m[20][10]){
			for(int i=0; i<Ninputs; i++){
				input[i]=m[i/10][i%10];
			}
			calculate();
		}
		void test(float  *in){
			for(int i=0; i<Ninputs; i++){
				input[i]=in[i];
			}
			calculate();
		}
		float  tsse(){
			float  r=0;
			for(int k=0; k<Noutputs; k++){
				r+=(target[k]-output[k])*(target[k]-output[k]);
			}
			return r;
		}
		float  rmse(float  Npatterns){
			return sqrt((tsse())/(Npatterns*Noutputs));
		}
};


