<?php

/**
 * @file
 * Provides functions for setting up the site wide status.
 */


/**
 * Author : Stephen Blinkhorne
 *  stephen.blinkhorne@talquin.com
 * 
 * Created 30th July 2013
 * 
 */

/**
 * Show the form to allow the user to change the settings.
 *
 * @param 
 *   none
 *
 * @return
 *   Form array to be rendered
 */
function film_links_settings($form, &$form_state) {

  // Give some information on the setting up process.
  // Might need to add code to prevent or warn user if they decide to change it

//  $output['title'] = array(
//      '#markup' => t('Film link set up'),
//      '#weight' => 1,
//      '#prefix' => '<h1>',
//      '#suffix' => '</h1>',        
//    );
//
//  $output['description'] = array(
//      '#markup' => 'Film set up options.',
//  
//  );
  
  $buttons = variable_get('film_general_buttons', array(
    'people_edit_crew' => '',
    'people_edit_cast' => '',
    'people_edit_crew_organisation' => '',
    'film_edit_crew' => '',
    'film_edit_cast' => '',
    'organisation_edit' => '',
    'film_edit_crew_organisation' => '',
  ));

  $form['film_general_buttons'] = array(
    '#prefix' => '<a id="buttons"></a>',
    '#type' => 'fieldset',
    '#title' => t('Buttons'),
    '#description' => t('The text sections required for the introductory page of the eligibility form.'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
    '#tree' => TRUE,

    'people_edit_crew' => array(
      '#type' => 'textfield',
      '#title' => t('People edit crew'),
  //    '#description' => t('Enter the text dealing with the research being carried out.'),
      '#default_value' => !empty($buttons['people_edit_crew'])?$buttons['people_edit_crew']:'',
    ),

    'people_edit_crew_organisation' => array(
      '#type' => 'textfield',
      '#title' => t('People edit for organisation content type'),
  //    '#description' => t('Enter the text dealing with the research being carried out.'),
      '#default_value' => !empty($buttons['people_edit_crew_organisation'])?$buttons['people_edit_crew_organisation']:'',
    ),    

    'people_edit_cast' => array(
      '#type' => 'textfield',
      '#title' => t('People edit cast'),
  //    '#description' => t('Enter the invitation text.'),
      '#default_value' => !empty($buttons['people_edit_cast'])?$buttons['people_edit_cast']:'',
    ),
    
    'film_edit_crew' => array(
      '#type' => 'textfield',
      '#title' => t('Film edit crew'),
  //    '#description' => t('Enter the text dealing with the research being carried out.'),
      '#default_value' => !empty($buttons['film_edit_crew'])?$buttons['film_edit_crew']:'',
    ),
    
    'film_edit_crew_organisation' => array(
      '#type' => 'textfield',
      '#title' => t('Film edit for organisation content type'),
  //    '#description' => t('Enter the text dealing with the research being carried out.'),
      '#default_value' => !empty($buttons['film_edit_crew_organisation'])?$buttons['film_edit_crew_organisation']:'',
    ),     

    'film_edit_cast' => array(
      '#type' => 'textfield',
      '#title' => t('Film edit cast'),
  //    '#description' => t('Enter the invitation text.'),
      '#default_value' => !empty($buttons['film_edit_cast'])?$buttons['film_edit_cast']:'',
    ),    
    
    'organisation_edit' => array(
      '#type' => 'textfield',
      '#title' => t('Organisation edit'),
  //    '#description' => t('Enter the invitation text.'),
      '#default_value' => !empty($buttons['organisation_edit'])?$buttons['organisation_edit']:'',
    ),   
  );

  
  $organisation = variable_get('film_general_organisation', array(
    'message_film' => '',
    'message_people' => '',
    'role_title_film' => '',
    'role_title_people' => '',
    'main_title_film' => '',
    'main_title_people' => '',
  ));

  $form['film_general_organisation'] = array(
    '#prefix' => '<a id="buttons"></a>',
    '#type' => 'fieldset',
    '#title' => t('Organisation labels'),
    '#description' => t('.'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
    '#tree' => TRUE,

   'text_film' => array(
      '#markup' => t('<h2>Film -> Organisation</h2><p>These labels are for the screen when you click on the edit organisation button on the film page'),
    ),

    'main_title_film' => array(
      '#type' => 'textfield',
      '#title' => t('Main title'),
      '#default_value' => !empty($organisation['main_title_film'])?$organisation['main_title_film']:'',
    ),
    
    'message_film' => array(
      '#type' => 'textarea',
      '#title' => t('Top message'),
      '#default_value' => !empty($organisation['message_film'])?$organisation['message_film']:'',
    ),

    'organisation_film' => array(
      '#type' => 'textfield',
      '#title' => t('Label for organisation autocomplete'),
      '#default_value' => !empty($organisation['organisation_film'])?$organisation['organisation_film']:'',
    ),

    'role_title_film' => array(
      '#type' => 'textfield',
      '#title' => t('Role label'),
      '#default_value' => !empty($organisation['role_title_film'])?$organisation['role_title_film']:'',
    ),  
    'submit_film' => array(
      '#type' => 'textfield',
      '#title' => t('Submit button'),
      '#default_value' => !empty($organisation['submit_film'])?$organisation['submit_film']:'',
    ),    
   'text_people' => array(
      '#markup' => t('<h2>People -> Organisation</h2>'),
    ),
    'main_title_people' => array(
      '#type' => 'textfield',
      '#title' => t('Main title for film / people'),
      '#default_value' => !empty($organisation['main_title_people'])?$organisation['main_title_people']:'',
    ),
    'message_people' => array(
      '#type' => 'textarea',
      '#title' => t('message film / people'),
      '#default_value' => !empty($organisation['message_people'])?$organisation['message_people']:'',
      
    ),    

    'organisation_people' => array(
      '#type' => 'textfield',
      '#title' => t('Label for organisation autocomplete'),
      '#default_value' => !empty($organisation['organisation_people'])?$organisation['organisation_people']:'',
    ),
    'role_title_people' => array(
      '#type' => 'textfield',
      '#title' => t('Role label'),
      '#default_value' => !empty($organisation['role_title_people'])?$organisation['role_title_people']:'',
    ), 
    'submit_people' => array(
      '#type' => 'textfield',
      '#title' => t('Submit button'),
      '#default_value' => !empty($organisation['submit_people'])?$organisation['submit_people']:'',
    ),        
  );  

 //----------------------------------------------------------------------------- 
  $people = variable_get('film_general_people', array(
    'message_film' => '',
    'message_people' => '',
    'role_title_film' => '',
    'role_title_people' => '',
    'main_title_film' => '',
    'main_title_people' => '',
  ));

  $form['film_general_people'] = array(
    '#prefix' => '<a id="buttons"></a>',
    '#type' => 'fieldset',
    '#title' => t('People labels'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
    '#tree' => TRUE,

   'text_film_Cast' => array(
      '#markup' => t('<h2>Film -> People (cast)</h2><p>These labels are for teh screen when you click on the edit people button on the film page</p>'),
    ),

    'main_title_film_cast' => array(
      '#type' => 'textfield',
      '#title' => t('Main title'),
      '#default_value' => !empty($people['main_title_film_cast'])?$people['main_title_film_cast']:'',
    ),
    
    'message_film_cast' => array(
      '#type' => 'textarea',
      '#title' => t('Top message'),
      '#default_value' => !empty($people['message_film_cast'])?$people['message_film_cast']:'',
    ),

    'person_film_cast' => array(
      '#type' => 'textfield',
      '#title' => t('Label for person autocomplete'),
      '#default_value' => !empty($people['person_film_cast'])?$people['person_film_cast']:'',
    ),

    'character_film_cast' => array(
      '#type' => 'textfield',
      '#title' => t('Character label'),
      '#default_value' => !empty($people['character_film_cast'])?$people['character_film_cast']:'',
    ),  
    'submit_film_cast' => array(
      '#type' => 'textfield',
      '#title' => t('Submit button'),
      '#default_value' => !empty($people['submit_film_cast'])?$people['submit_film_cast']:'',
    ),    
    
   'text_film_crew' => array(
      '#markup' => t('<h2>Film -> People (crew)</h2><p>These labels are for teh screen when you click on the edit people button on the film page</p>'),
    ),

    'main_title_film_crew' => array(
      '#type' => 'textfield',
      '#title' => t('Main title'),
      '#default_value' => !empty($people['main_title_film_crew'])?$people['main_title_film_crew']:'',
    ),
    
    'message_film_crew' => array(
      '#type' => 'textarea',
      '#title' => t('Top message'),
      '#default_value' => !empty($people['message_film_crew'])?$people['message_film_crew']:'',
    ),

    'person_film_crew' => array(
      '#type' => 'textfield',
      '#title' => t('Label for person autocomplete'),
      '#default_value' => !empty($people['person_film_crew'])?$people['person_film_crew']:'',
    ),

    'role_title_film_crew' => array(
      '#type' => 'textfield',
      '#title' => t('Role label'),
      '#default_value' => !empty($people['role_title_film_crew'])?$people['role_title_film_crew']:'',
    ),  
    'submit_film_crew' => array(
      '#type' => 'textfield',
      '#title' => t('Submit button'),
      '#default_value' => !empty($people['submit_film_crew'])?$people['submit_film_crew']:'',
    ),
    
   'text_people' => array(
      '#markup' => t('<h2>Organisation -> People</h2><p>These labels are for teh screen when you click on the edit people button on the organisation page'),
    ),
    'main_title_organisation' => array(
      '#type' => 'textfield',
      '#title' => t('Main title for film / people'),
      '#default_value' => !empty($people['main_title_organisation'])?$people['main_title_organisation']:'',
    ),
    'message_organisation' => array(
      '#type' => 'textarea',
      '#title' => t('message film / people'),
      '#default_value' => !empty($people['message_organisation'])?$people['message_organisation']:'',
      
    ),    

    'person_organisation' => array(
      '#type' => 'textfield',
      '#title' => t('Label for person autocomplete'),
      '#default_value' => !empty($people['person_organisation'])?$people['person_organisation']:'',
    ),
    'role_title_people' => array(
      '#type' => 'textfield',
      '#title' => t('Role label'),
      '#default_value' => !empty($people['role_title_people'])?$people['role_title_people']:'',
    ), 
    'submit_organisation' => array(
      '#type' => 'textfield',
      '#title' => t('Submit button'),
      '#default_value' => !empty($people['submit_organisation'])?$people['submit_organisation']:'',
    ),        
  );   

 //----------------------------------------------------------------------------- 
  $film = variable_get('film_general_film', array(
    'message_film' => '',
    'message_people' => '',
    'role_title_film' => '',
    'role_title_people' => '',
    'main_title_film' => '',
    'main_title_people' => '',
  ));

  $form['film_general_film'] = array(
    '#prefix' => '<a id="buttons"></a>',
    '#type' => 'fieldset',
    '#title' => t('Film labels'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
    '#tree' => TRUE,

   'text_film_Cast' => array(
      '#markup' => t('<h2>People -> Film (cast)</h2><p>These labels are for teh screen when you click on the edit people button on the film page</p>'),
    ),

    'main_title_film_cast' => array(
      '#type' => 'textfield',
      '#title' => t('Main title'),
      '#default_value' => !empty($film['main_title_film_cast'])?$film['main_title_film_cast']:'',
    ),
    
    'message_film_cast' => array(
      '#type' => 'textarea',
      '#title' => t('Top message'),
      '#default_value' => !empty($film['message_film_cast'])?$film['message_film_cast']:'',
    ),

    'film_film_cast' => array(
      '#type' => 'textfield',
      '#title' => t('Label for film autocomplete'),
      '#default_value' => !empty($film['film_film_cast'])?$film['film_film_cast']:'',
    ),

    'character_film_cast' => array(
      '#type' => 'textfield',
      '#title' => t('Character label'),
      '#default_value' => !empty($film['character_film_cast'])?$film['character_film_cast']:'',
    ),  
    'submit_film_cast' => array(
      '#type' => 'textfield',
      '#title' => t('Submit button'),
      '#default_value' => !empty($film['submit_film_cast'])?$film['submit_film_cast']:'',
    ),    
    
   'text_film_crew' => array(
      '#markup' => t('<h2>People -> Film (crew)</h2><p>These labels are for teh screen when you click on the edit people button on the film page</p>'),
    ),

    'main_title_film_crew' => array(
      '#type' => 'textfield',
      '#title' => t('Main title'),
      '#default_value' => !empty($film['main_title_film_crew'])?$film['main_title_film_crew']:'',
    ),
    
    'message_film_crew' => array(
      '#type' => 'textarea',
      '#title' => t('Top message'),
      '#default_value' => !empty($film['message_film_crew'])?$film['message_film_crew']:'',
    ),

    'film_film_crew' => array(
      '#type' => 'textfield',
      '#title' => t('Label for film autocomplete'),
      '#default_value' => !empty($film['film_film_crew'])?$film['film_film_crew']:'',
    ),

    'role_title_film_crew' => array(
      '#type' => 'textfield',
      '#title' => t('Role label'),
      '#default_value' => !empty($film['role_title_film_crew'])?$film['role_title_film_crew']:'',
    ),  
    'submit_film_crew' => array(
      '#type' => 'textfield',
      '#title' => t('Submit button'),
      '#default_value' => !empty($film['submit_film_crew'])?$film['submit_film_crew']:'',
    ),
    
   'text_people' => array(
      '#markup' => t('<h2>Organisation -> film</h2><p>These labels are for teh screen when you click on the edit people button on the organisation page'),
    ),
    'main_title_organisation' => array(
      '#type' => 'textfield',
      '#title' => t('Main title for film / people'),
      '#default_value' => !empty($film['main_title_organisation'])?$film['main_title_organisation']:'',
    ),
    'message_organisation' => array(
      '#type' => 'textarea',
      '#title' => t('message film / people'),
      '#default_value' => !empty($film['message_organisation'])?$film['message_organisation']:'',
      
    ),    

    'film_organisation' => array(
      '#type' => 'textfield',
      '#title' => t('Label for film autocomplete'),
      '#default_value' => !empty($film['film_organisation'])?$film['film_organisation']:'',
    ),
    'role_title_film' => array(
      '#type' => 'textfield',
      '#title' => t('Role label'),
      '#default_value' => !empty($film['role_title_film'])?$film['role_title_film']:'',
    ), 
    'submit_organisation' => array(
      '#type' => 'textfield',
      '#title' => t('Submit button'),
      '#default_value' => !empty($film['submit_organisation'])?$film['submit_organisation']:'',
    ),        
  );  
  return system_settings_form($form);
}

