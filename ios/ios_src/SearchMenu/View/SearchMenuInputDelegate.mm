// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "SearchMenuInputDelegate.h"

#include "SearchMenuViewInterop.h"
#include "UIColors.h"

@interface SearchMenuInputDelegate()
{
    UITextField* m_pTextField;
    UIButton* m_pClearButton;
    SearchMenuResultsSpinner* m_pResultsSpinner;
    ExampleApp::SearchMenu::View::SearchMenuViewInterop* m_pInterop;
    
    BOOL m_keyboardActive;
    BOOL m_returnPressed;
    BOOL m_currentSearchIsCategory;
    BOOL m_hasResults;
    BOOL m_searchInProgress;
}

@end

@implementation SearchMenuInputDelegate

- (id)initWithTextField:(UITextField*)textField
            clearButton:(UIButton*)clearButton
         resultsSpinner:(SearchMenuResultsSpinner*)resultsSpinner
                interop:(ExampleApp::SearchMenu::View::SearchMenuViewInterop*)interop
{
    m_hasResults = NO;
    m_pTextField = textField;
    m_pClearButton = clearButton;
    m_pResultsSpinner = resultsSpinner;
    m_pInterop = interop;
    
    m_pTextField.delegate = self;
    
    [m_pClearButton addTarget:self action:@selector(clearSearch) forControlEvents:UIControlEventTouchUpInside];
    
    [self updateClearButtonVisibility];
    
    m_keyboardActive = false;
    m_returnPressed = false;
    m_currentSearchIsCategory = false;
    m_searchInProgress = false;
    
    [[NSNotificationCenter defaultCenter]addObserver:self
                                            selector:@selector(keyboardDidChangeFrame:)
                                                name:UIKeyboardDidChangeFrameNotification
                                              object:nil];
    
    [[NSNotificationCenter defaultCenter] addObserver:self
                                             selector:@selector(textFieldTextDidChange:)
                                                 name:UITextFieldTextDidChangeNotification
                                               object:m_pTextField];
    
    return self;
}

- (void)dealloc
{
    [[NSNotificationCenter defaultCenter] removeObserver:self
                                                    name:UITextFieldTextDidChangeNotification
                                                  object:m_pTextField];
    
    [[NSNotificationCenter defaultCenter]removeObserver:self
                                                   name:UIKeyboardDidChangeFrameNotification
                                                 object:nil];
    
    m_pTextField.delegate = nil;
    
    [super dealloc];
}

- (void) setSearchInProgress
{
    [m_pResultsSpinner startAnimating];
    m_searchInProgress = true;
    [self updateClearButtonVisibility];
}

- (void) setSearchEnded
{
    [m_pResultsSpinner stopAnimating];
    m_searchInProgress = false;
    [self updateClearButtonVisibility];
}

- (void) removeSeachKeyboard
{
    [m_pTextField resignFirstResponder];
}

- (void) setEditText :(NSString*)searchText
                     :(bool)isCategory
{
    if(![m_pTextField isEditing])
    {
        [m_pTextField setText:searchText];
    }
    
    m_currentSearchIsCategory = isCategory;
    
    [self updateClearButtonVisibility];
}

- (void) clearSearch
{
    m_pInterop->OnSearchCleared();
    
    m_pTextField.text = @"";
    
    [self updateClearButtonVisibility];
}

- (void) setHasResults :(bool)hasResults
{
    m_hasResults = hasResults;
    [self updateClearButtonVisibility];
}

- (void)updateClearButtonVisibility
{
    m_pClearButton.hidden = !m_hasResults || m_searchInProgress;
}

- (void)textFieldTextDidChange:(NSNotification*)aNotification
{
    if(aNotification.object != m_pTextField)
    {
        return;
    }
    
    [self updateClearButtonVisibility];
}

- (void)keyboardDidChangeFrame:(NSNotification*)aNotification
{
    if (m_keyboardActive)
    {
        [m_pTextField becomeFirstResponder];
    }
}

- (void)textFieldDidBeginEditing:(UITextField *)textField
{
    m_keyboardActive = true;
    m_returnPressed = false;
    
    if(m_currentSearchIsCategory)
    {
        [textField setText:@""];
        m_currentSearchIsCategory = false;
        
        [self updateClearButtonVisibility];
    }
}

- (BOOL)textFieldShouldReturn:(UITextField *)textField
{
    m_returnPressed = true;
    [textField resignFirstResponder];
    return TRUE;
}

- (void)textFieldDidEndEditing:(UITextField *)textField
{
    m_keyboardActive = false;
    
    if (!m_returnPressed || [textField.text isEqualToString:@""])
    {
        return;
    }
    
    std::string searchString = [textField.text UTF8String];
    m_pInterop->SearchPerformed(searchString);
}

- (BOOL)textFieldShouldClear:(UITextField *)textField
{
    m_pInterop->OnSearchCleared();
    
    textField.text = @"";
    
    [self updateClearButtonVisibility];
    return NO;
}

@end