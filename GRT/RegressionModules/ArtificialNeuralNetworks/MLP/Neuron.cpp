/*
GRT MIT License
Copyright (c) <2012> <Nicholas Gillian, Media Lab, MIT>

Permission is hereby granted, free of charge, to any person obtaining a copy of this software 
and associated documentation files (the "Software"), to deal in the Software without restriction, 
including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, 
and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, 
subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial 
portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT 
LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. 
IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, 
WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE 
SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

#include "Neuron.h"

namespace GRT{

Neuron::Neuron(){
	activationFunction = LINEAR;
	numInputs = 0;
	gamma = 2.0;
	bias = 0;
	previousBiasUpdate = 0;
}

Neuron::~Neuron(){}

void Neuron::init(unsigned int numInputs,unsigned int activationFunction){
    
    this->numInputs = numInputs;
    this->activationFunction = activationFunction;
    
    weights.resize(numInputs);
	previousUpdate.resize(numInputs);
    
    //Set the random seed
    random.setSeed( (unsigned long long)time(NULL) );
    
    //Randomise the weights between [-0.1 0.1]
    //Note, it's better to set the random values using small weights rather than [-1.0 1.0]
    for(unsigned int i=0; i<numInputs; i++){
        weights[i] = random.getRandomNumberUniform(-0.1,0.1);
		previousUpdate[i] = 0;
    }

	//Randomise the bias between [-0.1 1.0]
	 bias = random.getRandomNumberUniform(-0.1,0.1);
	 previousBiasUpdate = 0;
}

void Neuron::clear(){
    numInputs = 0;
	bias = 0;
	previousBiasUpdate = 0;
    weights.clear();
	previousUpdate.clear();
}

double Neuron::fire(const VectorDouble &inputs){
    
    double y = 0;
    for(UINT i=0; i<numInputs; i++){
        y += inputs[i] * weights[i];
    }
    
    y += bias;
    
    switch( activationFunction ){
        case(LINEAR):
            break;
        case(SIGMOID):
			//Trick for stopping overflow
			if( y < -45.0 ){ y = 0; }
			else if( y > 45.0 ){ y = 1.0; }
			else{
				y = 1.0/(1.0+exp(-y));
			}
            break;
        case(BIPOLAR_SIGMOID):
			if( y < -45.0 ){ y = 0; }
			else if( y > 45.0 ){ y = 1.0; }
			else{
				y = (2 / (1 + exp(-gamma * y))) - 1.0;
			}
            break;
    }
    return y;
    
}

double Neuron::der(double y){

	double yy = 0;
	switch( activationFunction ){
        case(LINEAR):
			yy = 1.0;
            break;
        case(SIGMOID):
			yy = y * (1.0 - y);
            break;
        case(BIPOLAR_SIGMOID):
			yy = (gamma * (1.0 - (y*y))) / 2.0;
            break;
    }
    return yy;
}

}//End of namespace GRT