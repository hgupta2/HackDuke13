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

#ifndef GRT_REGRESSIFIER_HEADER
#define GRT_REGRESSIFIER_HEADER

#include "MLBase.h"
#include "../DataStructures/LabelledClassificationData.h"
#include "../DataStructures/LabelledTimeSeriesClassificationData.h"

namespace GRT{
    
#define DEFAULT_NULL_LIKELIHOOD_VALUE 0
#define DEFAULT_NULL_DISTANCE_VALUE 0

class Regressifier : public MLBase
{
public:
	Regressifier(void);
    
	virtual ~Regressifier(void);
    
    virtual bool deepCopyFrom(const Regressifier *regressifier){ return false; }
    
    Regressifier* deepCopy() const;
    
	/**
     This copies the Regressifier variables from the regressifier pointer to this instance.
     
     @param const Regressifier *regressifier: a pointer to a regressifier from which the values will be copied to this instance
     @return returns true if the copy was successfull, false otherwise
     */
    bool copyBaseVariables(const Regressifier *regressifier);

    /**
     This is the main training interface for all the regression algorithms.
     
     @param LabelledRegressionData trainingData: the training data that will be used to train a new regression model
     @return returns true if a new regression model was trained, false otherwise
     */
    virtual bool train(LabelledRegressionData trainingData){ return false; }
    
    /**
     Gets the regressifier type as a string. This is the name of the regression algorithm, such as "LinearRegression".
     
     @return returns the regressifier type as a string
     */
    string getRegressifierType() const;
    
    /**
     Gets the root mean squared error on the training data during the training phase.
     
     @return returns the RMS error (on the training data during the training phase)
     */
    double getRootMeanSquaredTrainingError() const;
    
    /**
     Gets the total squared error on the training data during the training phase.
     
     @return returns the total squared error (on the training data during the training phase)
     */
    double getTotalSquaredTrainingError() const;

    /**
     Gets a vector containing the regression data output by the regression algorithm, this will be an M-dimensional vector, where M is the number of output dimensions in the model.  
     
     @return returns a vector containing the regression data output by the regression algorithm, an empty vector will be returned if the model has not been trained
     */
    VectorDouble getRegressionData() const;

    /**
     Defines a map between a string (which will contain the name of the regressifier, such as LinearRegression) and a function returns a new instance of that regressifier
     */
    typedef std::map< string, Regressifier*(*)() > StringRegressifierMap;

    /**
     Creates a new regressifier instance based on the input string (which should contain the name of a valid regressifier such as LinearRegression).
     
     @param string const &regressifierType: the name of the regressifier
     @return Regressifier*: a pointer to the new instance of the regressifier
     */
    static Regressifier* createInstanceFromString(string const &regressifierType);

    /**
     Creates a new regressifier instance based on the current regressifierType string value.
     
     @return Regressifier*: a pointer to the new instance of the regressifier
    */
    Regressifier* createNewInstance() const;
    
protected:
    string regressifierType;
    double rootMeanSquaredTrainingError;
    double totalSquaredTrainingError;
    VectorDouble regressionData;
    vector< MinMax > inputVectorRanges;
	vector< MinMax > targetVectorRanges;
    
    static StringRegressifierMap *getMap() {
        if( !stringRegressifierMap ){ stringRegressifierMap = new StringRegressifierMap; } 
        return stringRegressifierMap; 
    }
    
private:
    static StringRegressifierMap *stringRegressifierMap;
    static UINT numRegressifierInstances;

};
    
//These two functions/classes are used to register any new Regression Module with the Regressifier base class
template< typename T >  Regressifier *newRegressionModuleInstance() { return new T; }

template< typename T > 
class RegisterRegressifierModule : Regressifier { 
public:
    RegisterRegressifierModule(string const &newRegresionModuleName) { 
        getMap()->insert( std::pair<string, Regressifier*(*)()>(newRegresionModuleName, &newRegressionModuleInstance< T > ) );
    }
};

} //End of namespace GRT

#endif //GRT_REGRESSIFIER_HEADER

