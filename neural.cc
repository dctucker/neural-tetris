#define WeightI(i,j) weightIn[i*Ninputs+j]
#define WeightO(i,j) weightOut[i*Nhidden+j]

class NeuralNet {
	private:
		double *output, *hidden,
			   *weightIn,*weightOut,
			   *biasHid,*biasOut,
			   *errorHid, *errorOut;
		int Ninputs,Nhidden,Noutputs;
	public:
		double *input,*target;
		double bias, eta,RMSE;
	private:
		double sigmoid(double x){
			return 1.0 / ( 1.0 + exp(-x) );
		}
		void initWeights(){
			for(int i=0; i<Ninputs; i++){
				for(int j=0; j<Nhidden; j++){
					WeightI(i,j)=(2.4/(double)Ninputs)*rho;
				}
			}
			for(int i=0; i<Nhidden; i++){
				biasHid[i]=(2.4/(double)Ninputs)*rho;;
				for(int j=0; j<Noutputs;j++){
					WeightO(i,j)=(2.4/(double)Ninputs)*(rho);
					if(i==0) biasOut[j]=(2.4/(double)Ninputs)*rho;
				}
			}
		}
	public:
		NeuralNet(int ni,int nh,int no){
			bias=0.3;
			eta=0.8;
			
			Ninputs=ni;
			Nhidden=nh;
			Noutputs=no;
			
			input = new double[Ninputs];
			target= new double[Noutputs];
			
			hidden= new double[Nhidden];
			output= new double[Noutputs];
			
			weightIn= new double[Ninputs*Nhidden];
			weightOut=new double[Nhidden*Noutputs];
			
			biasHid=  new double[Nhidden];
			biasOut=  new double[Noutputs];

			errorHid= new double[Nhidden];
			errorOut= new double[Noutputs];
			
			initWeights();
		}
		void calculate(){
			double netj;
			for(int j=0; j<Nhidden; j++){
				double s=0;
				for(int i=0; i<Ninputs; i++){
					s+=input[i]*WeightI(i,j);
				}
				netj=s+bias*biasHid[j];
				hidden[j]=sigmoid(netj);
			}
			for(int k=0; k<Noutputs; k++){
				double s=0;
				for(int j=0; j<Nhidden; j++){
					s+=hidden[j]*WeightO(j,k);
				}
				netj=s+bias*biasOut[k];
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
				double s=0;
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
				biasOut[k] += eta*biasOut[k]*errorOut[k];
			}
			for(int j=0; j<Nhidden; j++){
				for(int i=0; i<Ninputs; i++){
					WeightI(i,j)+=eta*errorHid[j]*input[i];
				}
				biasHid[j]=eta*biasHid[j]*errorHid[j];
			}
		}
		void train(double *in, double *tar){
			for(int i=0; i<Ninputs; i++){
				input[i]=in[i];
			}
			for(int i=0; i<Noutputs; i++){
				target[i]=tar[i];
			}
			
			calculate();
			updateErrors();
			updateW();
		}
		void train(double *in, double tar){
			for(int i=0; i<Ninputs; i++){
				input[i]=in[i];
			}
			for(int i=0; i<Noutputs; i++){
				target[i]=tar;
			}
			
			calculate();
			updateErrors();
			updateW();
	
		}
		void test(double *in, double *tar, bool calc=true){
			for(int i=0; i<Ninputs; i++){
				input[i]=in[i];
			}
			for(int k=0; k<Noutputs; k++){
				target[k]=tar[k];
			}
			if(calc) calculate();
		}
		void test(double *in){
			for(int i=0; i<Ninputs; i++){
				input[i]=in[i];
			}
			calculate();
		}
		double getOutput(int k){
			return output[k];
		}


	/*********** printing methods **************/
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
			std::cout.precision(5);
			for(int k=0; k<Noutputs; k++)
				//std::cout << ((output[k]>0.7)?":":".") << (int)(output[k]*10)
				//   << ((int)(output[k]*100)%10) << " ";
				std::cout << output[k];
			std::cout << "\n";
		}
		void printT(){
			std::cout.precision(5);
			for(int k=0; k<Noutputs; k++)
				//std::cout << ((target[k]>0.7)?":":".") << (int)(target[k]*10)
				//	<< ((int)(target[k]*100)%10) << " ";
				std::cout << target[k];
			std::cout << "\n";
		}

		/****** other methods *******/
		void train(unsigned char m[20][10],double *tar){
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
		double tsse(){
			double r=0;
			for(int k=0; k<Noutputs; k++){
				r+=(target[k]-output[k])*(target[k]-output[k]);
			}
			return r;
		}
		double rmse(double Npatterns){
			return sqrt((tsse())/(Npatterns*Noutputs));
		}
};


