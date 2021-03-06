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
 The Class Label Change Filter signals when the predicted output of a classifier changes. For instance, if 
 the output stream of a classifier was {1,1,1,1,2,2,2,2,3,3}, then the output of the filter would be 
 {1,0,0,0,2,0,0,0,3,0}. This module is useful if you want to debounce a gesture and only care about when 
 the gesture label changes.
 */

#ifndef GRT_CLASS_LABEL_CHANGE_FILTER_HEADER
#define GRT_CLASS_LABEL_CHANGE_FILTER_HEADER

#include "../Util/GRTCommon.h"
#include "../GestureRecognitionPipeline/PostProcessing.h"

namespace GRT{
    
class ClassLabelChangeFilter : public PostProcessing{
public:
    /**
     Default Constructor. 
     */
    ClassLabelChangeFilter();
    
    /**
     Copy Constructor.
     
     Copies the values from the rhs ClassLabelChangeFilter to this instance of the ClassLabelChangeFilter.
     
     @param const ClassLabelChangeFilter &rhs: the rhs from which the values will be copied to this this instance of the ClassLabelChangeFilter
     */
    ClassLabelChangeFilter(const ClassLabelChangeFilter &rhs);
    
    /**
     Default Destructor
     */
	virtual ~ClassLabelChangeFilter();
    
    /**
     Assigns the equals operator setting how the values from the rhs instance will be copied to this instance.
     
     @param const ClassLabelChangeFilter &rhs: the rhs instance from which the values will be copied to this this instance of the ClassLabelChangeFilter
     @return returns a reference to this instance of the ClassLabelChangeFilter
     */
    ClassLabelChangeFilter& operator=(const ClassLabelChangeFilter &rhs);
    
    /**
     Sets the PostProcessing clone function, overwriting the base PostProcessing function.
     This function is used to clone the values from the input pointer to this instance of the PostProcessing module.
     This function is called by the GestureRecognitionPipeline when the user adds a new PostProcessing module to the pipeline.
     
     @param const PostProcessing *postProcessing: a pointer to another instance of a ClassLabelChangeFilter, the values of that instance will be cloned to this instance
	 @return true if the clone was successful, false otherwise
     */
    virtual bool clone(const PostProcessing *postProcessing);
    
    /**
     Sets the PostProcessing process function, overwriting the base PostProcessing function.
     This function is called by the GestureRecognitionPipeline when any new input data needs to be processed (during the prediction phase for example).
     This function calls the ClassLabelChangeFilter's filter(...) function.
     
     @param const vector< double > &inputVector: the inputVector that should be processed.  This should be a 1-dimensional vector containing a predicted class label
	 @return true if the data was processed, false otherwise
     */
    virtual bool process(const vector< double > &inputVector);
    
    /**
     Sets the PostProcessing reset function, overwriting the base PostProcessing function.
     This function is called by the GestureRecognitionPipeline when the pipelines main reset() function is called.
     This function resets the ClassLabelChangeFilter by re-initiliazing the instance.
     
     @return true if the ClassLabelChangeFilter was reset, false otherwise
     */
    virtual bool reset();
    
    /**
     This saves the post processing settings to a file.
     This overrides the saveSettingsToFile function in the PostProcessing base class.
     
     @param string filename: the name of the file to save the settings to
     @return returns true if the settings were saved successfully, false otherwise
     */
    virtual bool saveSettingsToFile(string filename);
    
    /**
     This saves the post processing settings to a file.
     This overrides the saveSettingsToFile function in the PostProcessing base class.
     
     @param string filename: the name of the file to save the settings to
     @return returns true if the settings were saved successfully, false otherwise
     */
    virtual bool saveSettingsToFile(fstream &file);
    
    /**
     This loads the post processing  settings from a file.
     This overrides the loadSettingsFromFile function in the PostProcessing base class.
     
     @param string filename: the name of the file to load the settings from
     @return returns true if the settings were loaded successfully, false otherwise
     */
    virtual bool loadSettingsFromFile(string filename);
    
    /**
     This loads the post processing settings from a file.
     This overrides the loadSettingsFromFile function in the PostProcessing base class.
     
     @param string filename: the name of the file to load the settings from
     @return returns true if the settings were loaded successfully, false otherwise
     */
    virtual bool loadSettingsFromFile(fstream &file);

    /**
     This function initializes the ClassLabelChangeFilter.
     
     @return returns true if the ClassLabelChangeFilter was initialized, false otherwise
     */
    bool init(); 
    
    /**
     This is the main filter function which filters the input predictedClassLabel.
     
     @param UINT predictedClassLabel: the predictedClassLabel which should be filtered
     return returns the filtered class label
     */
	UINT filter(UINT predictedClassLabel);
    
    /**
     Get the most recently filtered class label value.
     
     @return returns the filtered class label
     */
    UINT getFilteredClassLabel(){ return filteredClassLabel; }
    
    /**
     Get if the class label just changed.
     
     @return returns true if the class label just changed, false otherwise
     */
    bool getChange();
    
protected:
    UINT filteredClassLabel;
    bool labelChanged;
    
    static RegisterPostProcessingModule< ClassLabelChangeFilter > registerModule;
};

}//End of namespace GRT

#endif //GRT_CLASS_LABEL_CHANGE_FILTER_HEADER
