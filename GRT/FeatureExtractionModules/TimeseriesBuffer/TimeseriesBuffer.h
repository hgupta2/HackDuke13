/**
 @file
 @author  Nicholas Gillian <ngillian@media.mit.edu>
 @version 1.0
 
 @section LICENSE
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
 
 @section DESCRIPTION
 */

#ifndef GRT_TIMESERIES_BUFFER_HEADER
#define GRT_TIMESERIES_BUFFER_HEADER

#include "../../GestureRecognitionPipeline/FeatureExtraction.h"

namespace GRT{
    
class TimeseriesBuffer : public FeatureExtraction{
public:
    /**
     Constructor, sets the search window size, deadZoneThreshold, and the dimensionality of the input data.
     The search window size sets how much data should be held in memory and searched each time the update function is called.
     
     @param UINT bufferSize: sets the size of the timeseries buffer. Default value = 5
     @param UINT numDimensions: sets the number of dimensions that will be input to the feature extraction. Default value = 1
     */
    TimeseriesBuffer(UINT bufferSize = 5,UINT numDimensions = 1);
	
    /**
     Copy constructor, copies the TimeseriesBuffer from the rhs instance to this instance.
     
     @param const TimeseriesBuffer &rhs: another instance of the TimeseriesBuffer class from which the data will be copied to this instance
     */
    TimeseriesBuffer(const TimeseriesBuffer &rhs);
    
    /**
     Default Destructor
     */
    virtual ~TimeseriesBuffer();
    
    /**
     Sets the equals operator, copies the data from the rhs instance to this instance.
     
     @param const TimeseriesBuffer &rhs: another instance of the TimeseriesBuffer class from which the data will be copied to this instance
     @return a reference to this instance of TimeseriesBuffer
     */
    TimeseriesBuffer& operator=(const TimeseriesBuffer &rhs);

    /**
     Sets the FeatureExtraction clone function, overwriting the base FeatureExtraction function.
     This function is used to clone the values from the input pointer to this instance of the FeatureExtraction module.
     This function is called by the GestureRecognitionPipeline when the user adds a new FeatureExtraction module to the pipeleine.
     
     @param const FeatureExtraction *featureExtraction: a pointer to another instance of a TimeseriesBuffer, the values of that instance will be cloned to this instance
     @return returns true if the clone was successful, false otherwise
     */
    virtual bool clone(const FeatureExtraction *featureExtraction);
    
    /**
     Sets the FeatureExtraction computeFeatures function, overwriting the base FeatureExtraction function.
     This function is called by the GestureRecognitionPipeline when any new input data needs to be processed (during the prediction phase for example).
     This function calls the TimeseriesBuffer's update function.
     
     @param const VectorDouble &inputVector: the inputVector that should be processed.  Must have the same dimensionality as the FeatureExtraction module
     @return returns true if the data was processed, false otherwise
     */
    virtual bool computeFeatures(const VectorDouble &inputVector);
    
    /**
     Sets the FeatureExtraction reset function, overwriting the base FeatureExtraction function.
     This function is called by the GestureRecognitionPipeline when the pipelines main reset() function is called.
     This function resets the feature extraction by re-initiliazing the instance.
     
     @return true if the filter was reset, false otherwise
     */
    virtual bool reset();
    
    /**
     This saves the feature extraction settings to a file.
     This overrides the saveSettingsToFile function in the FeatureExtraction base class.
     
     @param string filename: the name of the file to save the settings to
     @return returns true if the settings were saved successfully, false otherwise (the base class always returns false)
     */
    virtual bool saveSettingsToFile(string filename);
    
    /**
     This loads the feature extraction settings from a file.
     This overrides the loadSettingsFromFile function in the FeatureExtraction base class.
     
     @param string filename: the name of the file to load the settings from
     @return returns true if the settings were loaded successfully, false otherwise (the base class always returns false)
     */
    virtual bool loadSettingsFromFile(string filename);
    
    /**
     This saves the feature extraction settings to a file.
     This overrides the saveSettingsToFile function in the FeatureExtraction base class.
     
     @param fstream &file: a reference to the file to save the settings to
     @return returns true if the settings were saved successfully, false otherwise
     */
    virtual bool saveSettingsToFile(fstream &file);
    
    /**
     This loads the feature extraction settings from a file.
     This overrides the loadSettingsFromFile function in the FeatureExtraction base class.
     
     @param fstream &file: a reference to the file to load the settings from
     @return returns true if the settings were loaded successfully, false otherwise
     */
    virtual bool loadSettingsFromFile(fstream &file);

    /**
     Initializes the TimeseriesBuffer, setting the bufferSize and the dimensionality of the data it will buffer.
     The search bufferSize and numDimensions values must be larger than 0.
     Sets all the data buffer values to zero.
     
     @param UINT bufferSize: sets the size of the timeseries buffer
     @param UINT numDimensions: sets the number of dimensions that will be input to the feature extraction
	 @return true if the TimeseriesBuffer was initiliazed, false otherwise
     */
    bool init(UINT bufferSize,UINT numDimensions);
    
    /**
     Updates the timeseries buffer with the new data x, this should only be called if the dimensionality of this instance was set to 1.
     
     @param double x: the value to add to the buffer, this should only be called if the dimensionality of the filter was set to 1
	 @return a vector containing the timeseries buffer, an empty vector will be returned if the buffer is not initialized
     */
	VectorDouble update(double x);
    
    /**
     Updates the timeseries buffer with the new data x, the dimensionality of x should match that of this instance.
     
     @param const VectorDouble &x: a vector containing the values to be processed, must be the same size as the numInputDimensions
	 @return a vector containing the timeseries buffer, an empty vector will be returned if the buffer is not initialized
     */
    VectorDouble update(const VectorDouble &x);
    
    /**
     Sets the timeseries buffer size.  The buffer size must be larger than zero.
     Calling this function will reset the feature extraction.
     
     @param UINT bufferSize: sets the size of the timeseries buffer
	 @return true if the bufferSize value was updated, false otherwise
     */
    bool setBufferSize(UINT bufferSize);

    /**
     Gets the buffer size.
     
     @return returns an unsigned int representing the buffer size, returns zero if the feature extraction module has not been initialized
     */
    UINT getBufferSize();

    /** 
     Gets the current values in the timeseries buffer.  
     An empty vector will be returned if the buffer has not been initialized.
     
     @return returns a vector containing the timeseries values, an empty vector will be returned if the module has not been initialized
     */
    vector< VectorDouble > getDataBuffer();
    
protected:
    UINT bufferSize;
    CircularBuffer< VectorDouble > dataBuffer;              ///< A buffer used to store the timeseries data
    
    static RegisterFeatureExtractionModule< TimeseriesBuffer > registerModule;
};

}//End of namespace GRT

#endif //GRT_TIMESERIES_BUFFER_HEADER
