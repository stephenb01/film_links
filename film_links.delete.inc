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
function _film_link_role_delete($link_id) {

  $destination = $_GET['destination'];
  _film_links_role_link_delete($link_id) ;

  // Return to the calling page.
  if (!empty($destination)) {
    drupal_goto($destination);
  } else {
    drupal_goto('/');
  }

}




/*
 * we delete all the roles and the sub roles
 */
function _film_links_role_link_delete($link_id) {
  // First we delete all the sub 
  // We need to make sure we don't delete everything which is the case if the 
  // role id is NULL
  if (!empty($link_id)) {
    $query = db_delete('film_links');
    $query->condition('lid',$link_id,'=');

    try {
      $query->execute();
    } catch (Exception $e) {
      drupal_set_message(t('An error occurred deleting a film link item. Check the log files for more information'),'error');
      watchdog('film_links','Error deleting item : ' . $e,NULL,WATCHDOG_ERROR);      
      return FALSE;
    }
  }
  return TRUE;
}
