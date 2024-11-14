

const char* index_page = "<script>"                                               \
				   "function passwordCheck(){"                              \
				   "var password = prompt(\"Please enter the password.\");" \
				   "if (password===\"pirsensor123\"){"                     \
				   "window.location=\"main.html\";"                        \
				   "} else{"                                                \
				   "while(password !==\"pirsensor123\"){"                  \
				   "password = prompt(\"Please enter the password.\");"     \
				   "}"                                                      \
				   "window.location=\"main.html\";"                        \
				   "}"                                                      \
				   "}"                                                      \
				   "window.onload=passwordCheck;"                           \
				   "</script>";

const char* main_page = "<!DOCTYPE html>"                                                                                                                                                             \
					"<html>"                                                                                                                                                                      \
					"<script src=\"https://ajax.googleapis.com/ajax/libs/jquery/3.6.0/jquery.min.js\"></script>"                                                                                  \
					"<head>"                                                                                                                                                                      \
					"<meta charset=\"utf-8\">"                                                                                                                                                    \
					"<title>Motion Control Pro Management</title>"                                                                                                                                \
					"<script>"                                                                                                                                                                    \
					"function submitFormInBackground() {"                                                                                                                                         \
					"event.preventDefault();"                                                                                                                                                     \
					"const form = document.getElementById('Form3');"                                                                                                                              \
					"const urlParams = new URLSearchParams();"                                                                                                                                    \
					"for (const element of form.elements) {"                                                                                                                                      \
					"  if (element.type !== 'button' && element.type !== 'submit') {"                                                                                                             \
					"    urlParams.append(element.name, element.value);"                                                                                                                          \
					"  }"                                                                                                                                                                         \
					"}"                                                                                                                                                                           \
					"const url = new URL(form.action);"                                                                                                                                           \
					"url.search = urlParams.toString();"                                                                                                                                          \
					"fetch(url)"                                                                                                                                                                  \
					".then(response => {"                                                                                                                                                         \
					"  if (!response.ok) {"                                                                                                                                                       \
					"    throw new Error(`HTTP error! status: ${response.status}`);"                                                                                                              \
					"  }"                                                                                                                                                                         \
					"alert('Done');"                                                                                                                                                              \
					"  return response.text(); "                                                                                                                                                  \
					"})"                                                                                                                                                                          \
					".then(data => {"                                                                                                                                                             \
					"  console.log('Form submitted successfully! Response:', data);"                                                                                                              \
					"})"                                                                                                                                                                          \
					".catch(error => {"                                                                                                                                                           \
					"  console.error('Error submitting form:', error);"                                                                                                                           \
					"});"                                                                                                                                                                         \
					"}"                                                                                                                                                                           \
					"function sendLink1() {"                                                                                                                                                      \
					"var selectBox = document.getElementById(\"mySelect1\");"                                                                                                                     \
					"var selectedValue = selectBox.options[selectBox.selectedIndex].value;"                                                                                                       \
					"$.ajax({"                                                                                                                                                                    \
					"url: \"/LOAD?TEST=\" + selectedValue,"                                                                                                                                       \
					"success: function(result) {"                                                                                                                                                 \
					"$(\"#div1\").html(result);"                                                                                                                                                  \
					"}"                                                                                                                                                                           \
					"});"                                                                                                                                                                         \
					"}"                                                                                                                                                                           \
					"function sendRequest(path) {"                                                                                                                                                \
					"$.ajax({"                                                                                                                                                                    \
					"url:path,"                                                                                                                                                                   \
					"type:'GET',"                                                                                                                                                                 \
					"success: function(response) {"                                                                                                                                               \
					"},"                                                                                                                                                                          \
					"error: function(){"                                                                                                                                                          \
					"console.error('eror');"                                                                                                                                                      \
					"}"                                                                                                                                                                           \
					"});"                                                                                                                                                                         \
					"}"                                                                                                                                                                           \
					"$(document).ready(function(){"                                                                                                                                               \
					"$('#Button1').click(function(){"                                                                                                                                             \
					"sendRequest('/CONTROL?button=1');"                                                                                                                                           \
					"});"                                                                                                                                                                         \
					"$('#Button2').click(function(){"                                                                                                                                             \
					"sendRequest('/CONTROL?button=2');"                                                                                                                                           \
					"});"                                                                                                                                                                         \
					"$('#Button3').click(function(){"                                                                                                                                             \
					"sendRequest('/CONTROL?button=3');"                                                                                                                                           \
					"});"                                                                                                                                                                         \
					"$('#Button4').click(function(){"                                                                                                                                             \
					"sendRequest('/CONTROL?button=4');"                                                                                                                                           \
					"});"                                                                                                                                                                         \
					"$('#Button5').click(function(){"                                                                                                                                             \
					"sendRequest('/CONTROL?button=5');"                                                                                                                                           \
					"});"                                                                                                                                                                         \
					"$('#Button6').click(function(){"                                                                                                                                             \
					"sendRequest('/CONTROL?button=6');"                                                                                                                                           \
					"});"                                                                                                                                                                         \
					"})"                                                                                                                                                                          \
					"</script>"                                                                                                                                                                   \
					"<style>"                                                                                                                                                                     \
					"body"                                                                                                                                                                        \
					"{"                                                                                                                                                                           \
					"background-color: #FFFFFF;"                                                                                                                                                  \
					"color: #000000;"                                                                                                                                                             \
					"font-family: Roboto;"                                                                                                                                                        \
					"font-weight: normal;"                                                                                                                                                        \
					"font-size: 13px;"                                                                                                                                                            \
					"line-height: 1.1875;"                                                                                                                                                        \
					"margin: 0;"                                                                                                                                                                  \
					"padding: 0;"                                                                                                                                                                 \
					"}"                                                                                                                                                                           \
					"a"                                                                                                                                                                           \
					"{"                                                                                                                                                                           \
					"color: #0000FF;"                                                                                                                                                             \
					"text-decoration: underline;"                                                                                                                                                 \
					"}"                                                                                                                                                                           \
					"a:visited"                                                                                                                                                                   \
					"{"                                                                                                                                                                           \
					"color: #800080;"                                                                                                                                                             \
					"}"                                                                                                                                                                           \
					"a:active"                                                                                                                                                                    \
					"{"                                                                                                                                                                           \
					"color: #FF0000;"                                                                                                                                                             \
					"}"                                                                                                                                                                           \
					"a:hover"                                                                                                                                                                     \
					"{"                                                                                                                                                                           \
					"color: #0000FF;"                                                                                                                                                             \
					"text-decoration: underline;"                                                                                                                                                 \
					"}"                                                                                                                                                                           \
					"input:focus, textarea:focus, select:focus"                                                                                                                                   \
					"{"                                                                                                                                                                           \
					"outline: none;"                                                                                                                                                              \
					"}"                                                                                                                                                                           \
					"</style>"                                                                                                                                                                    \
					"<link href=\"new_webpage.css\" rel=\"stylesheet\">"                                                                                                                          \
					"<style>"                                                                                                                                                                     \
					"#wb_Form3"                                                                                                                                                                   \
					"{"                                                                                                                                                                           \
					"background-color: #FBFBFB;"                                                                                                                                                  \
					"background-image: none;"                                                                                                                                                     \
					"border: 1px solid #CCCCCC;"                                                                                                                                                  \
					"border-radius: 13px;"                                                                                                                                                        \
					"}"                                                                                                                                                                           \
					"#wb_Heading4"                                                                                                                                                                \
					"{"                                                                                                                                                                           \
					"background-color: transparent;"                                                                                                                                              \
					"background-image: none;"                                                                                                                                                     \
					"border: 0px solid #000000;"                                                                                                                                                  \
					"border-radius: 0px;"                                                                                                                                                         \
					"margin: 0;"                                                                                                                                                                  \
					"padding: 0;"                                                                                                                                                                 \
					"text-align: center;"                                                                                                                                                         \
					"}"                                                                                                                                                                           \
					"#Heading4"                                                                                                                                                                   \
					"{"                                                                                                                                                                           \
					"color: #696969;"                                                                                                                                                             \
					"font-family: Roboto;"                                                                                                                                                        \
					"font-weight: bold;"                                                                                                                                                          \
					"font-style: normal;"                                                                                                                                                         \
					"font-size: 27px;"                                                                                                                                                            \
					"margin: 0;"                                                                                                                                                                  \
					"text-align: center;"                                                                                                                                                         \
					"}"                                                                                                                                                                           \
					"#Line1"                                                                                                                                                                      \
					"{"                                                                                                                                                                           \
					"border-color: #A0A0A0;"                                                                                                                                                      \
					"border-style: solid;"                                                                                                                                                        \
					"border-bottom-width: 3px;"                                                                                                                                                   \
					"border-top: 0px;"                                                                                                                                                            \
					"border-left: 0px;"                                                                                                                                                           \
					"border-right: 0px;"                                                                                                                                                          \
					"height: 0 !important;"                                                                                                                                                       \
					"line-height: 0px !important;"                                                                                                                                                \
					"margin: 0;"                                                                                                                                                                  \
					"padding: 0;"                                                                                                                                                                 \
					"}"                                                                                                                                                                           \
					"#wb_Form1"                                                                                                                                                                   \
					"{"                                                                                                                                                                           \
					"background-color: #FBFBFB;"                                                                                                                                                  \
					"background-image: none;"                                                                                                                                                     \
					"border: 1px solid #CCCCCC;"                                                                                                                                                  \
					"border-radius: 13px;"                                                                                                                                                        \
					"}"                                                                                                                                                                           \
					"#wb_Heading1"                                                                                                                                                                \
					"{"                                                                                                                                                                           \
					"background-color: transparent;"                                                                                                                                              \
					"background-image: none;"                                                                                                                                                     \
					"border: 0px solid #000000;"                                                                                                                                                  \
					"border-radius: 0px;"                                                                                                                                                         \
					"margin: 0;"                                                                                                                                                                  \
					"padding: 0;"                                                                                                                                                                 \
					"text-align: center;"                                                                                                                                                         \
					"}"                                                                                                                                                                           \
					"#Heading1"                                                                                                                                                                   \
					"{"                                                                                                                                                                           \
					"color: #696969;"                                                                                                                                                             \
					"font-family: \"Roboto\";"                                                                                                                                                     \
					"font-weight: bold;"                                                                                                                                                          \
					"font-style: normal;"                                                                                                                                                         \
					"font-size: 21px;"                                                                                                                                                            \
					"margin: 0;"                                                                                                                                                                  \
					"text-align: center;"                                                                                                                                                         \
					"}"                                                                                                                                                                           \
					".switch {"                                                                                                                                                                   \
					"position: relative;"                                                                                                                                                         \
					"display: inline-block;"                                                                                                                                                      \
					"width: 60px;"                                                                                                                                                                \
					"height: 34px;"                                                                                                                                                               \
					"}"                                                                                                                                                                           \
					""                                                                                                                                                                            \
					".switch input {"                                                                                                                                                             \
					"opacity: 0;"                                                                                                                                                                 \
					"width: 0;"                                                                                                                                                                   \
					"height: 0;"                                                                                                                                                                  \
					"}"                                                                                                                                                                           \
					""                                                                                                                                                                            \
					".slider {"                                                                                                                                                                   \
					"position: absolute;"                                                                                                                                                         \
					"cursor: pointer;"                                                                                                                                                            \
					"top: 0;"                                                                                                                                                                     \
					"left: 0;"                                                                                                                                                                    \
					"right: 0;"                                                                                                                                                                   \
					"bottom: 0;"                                                                                                                                                                  \
					"background-color: #ccc;"                                                                                                                                                     \
					"-webkit-transition: .4s;"                                                                                                                                                    \
					"transition: .4s;"                                                                                                                                                            \
					"}"                                                                                                                                                                           \
					""                                                                                                                                                                            \
					".slider:before {"                                                                                                                                                            \
					"position: absolute;"                                                                                                                                                         \
					"content: \"\";"                                                                                                                                                              \
					"height: 26px;"                                                                                                                                                               \
					"width: 26px;"                                                                                                                                                                \
					"left: 4px;"                                                                                                                                                                  \
					"bottom: 4px;"                                                                                                                                                                \
					"background-color: white;"                                                                                                                                                    \
					"-webkit-transition: .4s;"                                                                                                                                                    \
					"transition: .4s;"                                                                                                                                                            \
					"}"                                                                                                                                                                           \
					""                                                                                                                                                                            \
					"input:checked + .slider {"                                                                                                                                                   \
					"background-color: #2196F3;"                                                                                                                                                  \
					"}"                                                                                                                                                                           \
					""                                                                                                                                                                            \
					"input:focus + .slider {"                                                                                                                                                     \
					"box-shadow: 0 0 1px #2196F3;"                                                                                                                                                \
					"}"                                                                                                                                                                           \
					""                                                                                                                                                                            \
					"input:checked + .slider:before {"                                                                                                                                            \
					"-webkit-transform: translateX(26px);"                                                                                                                                        \
					"-ms-transform: translateX(26px);"                                                                                                                                            \
					"transform: translateX(26px);"                                                                                                                                                \
					"}"                                                                                                                                                                           \
					""                                                                                                                                                                            \
					"/* Rounded sliders */"                                                                                                                                                       \
					".slider.round {"                                                                                                                                                             \
					"border-radius: 34px;"                                                                                                                                                        \
					"}"                                                                                                                                                                           \
					""                                                                                                                                                                            \
					".slider.round:before {"                                                                                                                                                      \
					"border-radius: 50%;"                                                                                                                                                         \
					"}"                                                                                                                                                                           \
					"#Button1"                                                                                                                                                                    \
					"{"                                                                                                                                                                           \
					"border-top-width: 2px;"                                                                                                                                                      \
					"border-right-width: 4px;"                                                                                                                                                    \
					"border-bottom-width: 5px;"                                                                                                                                                   \
					"border-left-width: 2px;"                                                                                                                                                     \
					"border-top-style: solid;"                                                                                                                                                    \
					"border-right-style: ridge;"                                                                                                                                                  \
					"border-bottom-style: ridge;"                                                                                                                                                 \
					"border-left-style: ridge;"                                                                                                                                                   \
					"border-top-color: #000000;"                                                                                                                                                  \
					"border-right-color: #000000;"                                                                                                                                                \
					"border-bottom-color: #000000;"                                                                                                                                               \
					"border-left-color: #000000;"                                                                                                                                                 \
					"border-top-left-radius: 0px;"                                                                                                                                                \
					"border-top-right-radius: 2px;"                                                                                                                                               \
					"border-bottom-right-radius: 3px;"                                                                                                                                            \
					"border-bottom-left-radius: 1px;"                                                                                                                                             \
					"background-color: #F5F5F5;"                                                                                                                                                  \
					"background-image: none;"                                                                                                                                                     \
					"color: #202020;"                                                                                                                                                             \
					"font-family: Roboto;"                                                                                                                                                        \
					"font-weight: normal;"                                                                                                                                                        \
					"font-style: normal;"                                                                                                                                                         \
					"font-size: 19px;"                                                                                                                                                            \
					"padding: 1px 6px 1px 6px;"                                                                                                                                                   \
					"text-align: center;"                                                                                                                                                         \
					"-webkit-appearance: none;"                                                                                                                                                   \
					"margin: 0;"                                                                                                                                                                  \
					"}"                                                                                                                                                                           \
					"#Button2"                                                                                                                                                                    \
					"{"                                                                                                                                                                           \
					"border-top-width: 2px;"                                                                                                                                                      \
					"border-right-width: 4px;"                                                                                                                                                    \
					"border-bottom-width: 5px;"                                                                                                                                                   \
					"border-left-width: 2px;"                                                                                                                                                     \
					"border-top-style: solid;"                                                                                                                                                    \
					"border-right-style: ridge;"                                                                                                                                                  \
					"border-bottom-style: ridge;"                                                                                                                                                 \
					"border-left-style: ridge;"                                                                                                                                                   \
					"border-top-color: #000000;"                                                                                                                                                  \
					"border-right-color: #000000;"                                                                                                                                                \
					"border-bottom-color: #000000;"                                                                                                                                               \
					"border-left-color: #000000;"                                                                                                                                                 \
					"border-top-left-radius: 0px;"                                                                                                                                                \
					"border-top-right-radius: 2px;"                                                                                                                                               \
					"border-bottom-right-radius: 3px;"                                                                                                                                            \
					"border-bottom-left-radius: 1px;"                                                                                                                                             \
					"background-color: #F5F5F5;"                                                                                                                                                  \
					"background-image: none;"                                                                                                                                                     \
					"color: #202020;"                                                                                                                                                             \
					"font-family: Roboto;"                                                                                                                                                        \
					"font-weight: normal;"                                                                                                                                                        \
					"font-style: normal;"                                                                                                                                                         \
					"font-size: 19px;"                                                                                                                                                            \
					"padding: 1px 6px 1px 6px;"                                                                                                                                                   \
					"text-align: center;"                                                                                                                                                         \
					"-webkit-appearance: none;"                                                                                                                                                   \
					"margin: 0;"                                                                                                                                                                  \
					"}"                                                                                                                                                                           \
					"#Button3"                                                                                                                                                                    \
					"{"                                                                                                                                                                           \
					"border-top-width: 2px;"                                                                                                                                                      \
					"border-right-width: 4px;"                                                                                                                                                    \
					"border-bottom-width: 5px;"                                                                                                                                                   \
					"border-left-width: 2px;"                                                                                                                                                     \
					"border-top-style: solid;"                                                                                                                                                    \
					"border-right-style: ridge;"                                                                                                                                                  \
					"border-bottom-style: ridge;"                                                                                                                                                 \
					"border-left-style: ridge;"                                                                                                                                                   \
					"border-top-color: #000000;"                                                                                                                                                  \
					"border-right-color: #000000;"                                                                                                                                                \
					"border-bottom-color: #000000;"                                                                                                                                               \
					"border-left-color: #000000;"                                                                                                                                                 \
					"border-top-left-radius: 0px;"                                                                                                                                                \
					"border-top-right-radius: 2px;"                                                                                                                                               \
					"border-bottom-right-radius: 3px;"                                                                                                                                            \
					"border-bottom-left-radius: 1px;"                                                                                                                                             \
					"background-color: #F5F5F5;"                                                                                                                                                  \
					"background-image: none;"                                                                                                                                                     \
					"color: #202020;"                                                                                                                                                             \
					"font-family: Roboto;"                                                                                                                                                        \
					"font-weight: normal;"                                                                                                                                                        \
					"font-style: normal;"                                                                                                                                                         \
					"font-size: 19px;"                                                                                                                                                            \
					"padding: 1px 6px 1px 6px;"                                                                                                                                                   \
					"text-align: center;"                                                                                                                                                         \
					"-webkit-appearance: none;"                                                                                                                                                   \
					"margin: 0;"                                                                                                                                                                  \
					"}"                                                                                                                                                                           \
					"#Button4"                                                                                                                                                                    \
					"{"                                                                                                                                                                           \
					"border-top-width: 2px;"                                                                                                                                                      \
					"border-right-width: 4px;"                                                                                                                                                    \
					"border-bottom-width: 5px;"                                                                                                                                                   \
					"border-left-width: 2px;"                                                                                                                                                     \
					"border-top-style: solid;"                                                                                                                                                    \
					"border-right-style: ridge;"                                                                                                                                                  \
					"border-bottom-style: ridge;"                                                                                                                                                 \
					"border-left-style: ridge;"                                                                                                                                                   \
					"border-top-color: #000000;"                                                                                                                                                  \
					"border-right-color: #000000;"                                                                                                                                                \
					"border-bottom-color: #000000;"                                                                                                                                               \
					"border-left-color: #000000;"                                                                                                                                                 \
					"border-top-left-radius: 0px;"                                                                                                                                                \
					"border-top-right-radius: 2px;"                                                                                                                                               \
					"border-bottom-right-radius: 3px;"                                                                                                                                            \
					"border-bottom-left-radius: 1px;"                                                                                                                                             \
					"background-color: #F5F5F5;"                                                                                                                                                  \
					"background-image: none;"                                                                                                                                                     \
					"color: #202020;"                                                                                                                                                             \
					"font-family: Roboto;"                                                                                                                                                        \
					"font-weight: normal;"                                                                                                                                                        \
					"font-style: normal;"                                                                                                                                                         \
					"font-size: 19px;"                                                                                                                                                            \
					"padding: 1px 6px 1px 6px;"                                                                                                                                                   \
					"text-align: center;"                                                                                                                                                         \
					"-webkit-appearance: none;"                                                                                                                                                   \
					"margin: 0;"                                                                                                                                                                  \
					"}"                                                                                                                                                                           \
					"#Label2"                                                                                                                                                                     \
					"{"                                                                                                                                                                           \
					"border: 0px solid #000000;"                                                                                                                                                  \
					"border-radius: 4px;"                                                                                                                                                         \
					"background-color: transparent;"                                                                                                                                              \
					"background-image: none;"                                                                                                                                                     \
					"color: #696969;"                                                                                                                                                             \
					"font-family: \"Roboto\";"                                                                                                                                                    \
					"font-weight: normal;"                                                                                                                                                        \
					"font-style: normal;"                                                                                                                                                         \
					"font-size: 20px;"                                                                                                                                                            \
					"padding: 4px 4px 4px 4px;"                                                                                                                                                   \
					"margin: 0;"                                                                                                                                                                  \
					"text-align: center;"                                                                                                                                                         \
					"vertical-align: top;"                                                                                                                                                        \
					"}"                                                                                                                                                                           \
					"#wb_Form2"                                                                                                                                                                   \
					"{"                                                                                                                                                                           \
					"background-color: #FBFBFB;"                                                                                                                                                  \
					"background-image: none;"                                                                                                                                                     \
					"border: 1px solid #CCCCCC;"                                                                                                                                                  \
					"border-radius: 13px;"                                                                                                                                                        \
					"}"                                                                                                                                                                           \
					"#wb_Heading3"                                                                                                                                                                \
					"{"                                                                                                                                                                           \
					"background-color: transparent;"                                                                                                                                              \
					"background-image: none;"                                                                                                                                                     \
					"border: 0px solid #000000;"                                                                                                                                                  \
					"border-radius: 0px;"                                                                                                                                                         \
					"margin: 0;"                                                                                                                                                                  \
					"padding: 0;"                                                                                                                                                                 \
					"text-align: center;"                                                                                                                                                         \
					"}"                                                                                                                                                                           \
					"#Heading3"                                                                                                                                                                   \
					"{"                                                                                                                                                                           \
					"color: #696969;"                                                                                                                                                             \
					"font-family: \"Roboto\";"                                                                                                                                                    \
					"font-weight: bold;"                                                                                                                                                          \
					"font-style: normal;"                                                                                                                                                         \
					"font-size: 21px;"                                                                                                                                                            \
					"margin: 0;"                                                                                                                                                                  \
					"text-align: center;"                                                                                                                                                         \
					"}"                                                                                                                                                                           \
					"#Label1"                                                                                                                                                                     \
					"{"                                                                                                                                                                           \
					"border: 0px solid #000000;"                                                                                                                                                  \
					"border-radius: 4px;"                                                                                                                                                         \
					"background-color: transparent;"                                                                                                                                              \
					"background-image: none;"                                                                                                                                                     \
					"color: #000000;"                                                                                                                                                             \
					"font-family: \"Roboto\";"                                                                                                                                                    \
					"font-weight: normal;"                                                                                                                                                        \
					"font-style: normal;"                                                                                                                                                         \
					"font-size: 20px;"                                                                                                                                                            \
					"padding: 4px 4px 4px 4px;"                                                                                                                                                   \
					"margin: 0;"                                                                                                                                                                  \
					"text-align: left;"                                                                                                                                                           \
					"vertical-align: top;"                                                                                                                                                        \
					"}"                                                                                                                                                                           \
					"#Editbox1"                                                                                                                                                                   \
					"{"                                                                                                                                                                           \
					"border: 0px solid #DCDCDC;"                                                                                                                                                  \
					"border-radius: 0px;"                                                                                                                                                         \
					"background-color: #FBFBFB;"                                                                                                                                                  \
					"background-image: none;"                                                                                                                                                     \
					"color: #000000;"                                                                                                                                                             \
					"font-family: \"Roboto\";"                                                                                                                                                    \
					"font-weight: normal;"                                                                                                                                                        \
					"font-style: normal;"                                                                                                                                                         \
					"font-size: 17px;"                                                                                                                                                            \
					"line-height: 20px;"                                                                                                                                                          \
					"padding: 4px 4px 4px 4px;"                                                                                                                                                   \
					"margin: 0;"                                                                                                                                                                  \
					"text-align: center;"                                                                                                                                                         \
					"}"                                                                                                                                                                           \
					"#Editbox1:focus"                                                                                                                                                             \
					"{"                                                                                                                                                                           \
					"border-color: #66AFE9;"                                                                                                                                                      \
					"box-shadow: inset 0px 1px 1px rgba(0,0,0,0.075), 0px 0px 8px rgba(102,175,233,0.60);"                                                                                        \
					"outline: 0;"                                                                                                                                                                 \
					"}"                                                                                                                                                                           \
					"#Label3"                                                                                                                                                                     \
					"{"                                                                                                                                                                           \
					"border: 0px solid #000000;"                                                                                                                                                  \
					"border-radius: 4px;"                                                                                                                                                         \
					"background-color: transparent;"                                                                                                                                              \
					"background-image: none;"                                                                                                                                                     \
					"color: #000000;"                                                                                                                                                             \
					"font-family: \"Roboto\";"                                                                                                                                                    \
					"font-weight: normal;"                                                                                                                                                        \
					"font-style: normal;"                                                                                                                                                         \
					"font-size: 20px;"                                                                                                                                                            \
					"padding: 4px 4px 4px 4px;"                                                                                                                                                   \
					"margin: 0;"                                                                                                                                                                  \
					"text-align: left;"                                                                                                                                                           \
					"vertical-align: top;"                                                                                                                                                        \
					"}"                                                                                                                                                                           \
					"#Editbox2"                                                                                                                                                                   \
					"{"                                                                                                                                                                           \
					"border: 0px solid #DCDCDC;"                                                                                                                                                  \
					"border-radius: 0px;"                                                                                                                                                         \
					"background-color: #FBFBFB;"                                                                                                                                                  \
					"background-image: none;"                                                                                                                                                     \
					"color: #000000;"                                                                                                                                                             \
					"font-family: \"Roboto\";"                                                                                                                                                    \
					"font-weight: normal;"                                                                                                                                                        \
					"font-style: normal;"                                                                                                                                                         \
					"font-size: 17px;"                                                                                                                                                            \
					"line-height: 20px;"                                                                                                                                                          \
					"padding: 4px 4px 4px 4px;"                                                                                                                                                   \
					"margin: 0;"                                                                                                                                                                  \
					"text-align: center;"                                                                                                                                                         \
					"}"                                                                                                                                                                           \
					"#Editbox2:focus"                                                                                                                                                             \
					"{"                                                                                                                                                                           \
					"border-color: #66AFE9;"                                                                                                                                                      \
					"box-shadow: inset 0px 1px 1px rgba(0,0,0,0.075), 0px 0px 8px rgba(102,175,233,0.60);"                                                                                        \
					"outline: 0;"                                                                                                                                                                 \
					"}"                                                                                                                                                                           \
					"#Label4"                                                                                                                                                                     \
					"{"                                                                                                                                                                           \
					"border: 0px solid #000000;"                                                                                                                                                  \
					"border-radius: 4px;"                                                                                                                                                         \
					"background-color: transparent;"                                                                                                                                              \
					"background-image: none;"                                                                                                                                                     \
					"color: #000000;"                                                                                                                                                             \
					"font-family: \"Roboto\";"                                                                                                                                                    \
					"font-weight: normal;"                                                                                                                                                        \
					"font-style: normal;"                                                                                                                                                         \
					"font-size: 20px;"                                                                                                                                                            \
					"padding: 4px 4px 4px 4px;"                                                                                                                                                   \
					"margin: 0;"                                                                                                                                                                  \
					"text-align: left;"                                                                                                                                                           \
					"vertical-align: top;"                                                                                                                                                        \
					"}"                                                                                                                                                                           \
					"#Editbox3"                                                                                                                                                                   \
					"{"                                                                                                                                                                           \
					"border: 0px solid #DCDCDC;"                                                                                                                                                  \
					"border-radius: 0px;"                                                                                                                                                         \
					"background-color: #FBFBFB;"                                                                                                                                                  \
					"background-image: none;"                                                                                                                                                     \
					"color: #000000;"                                                                                                                                                             \
					"font-family: \"Roboto\";"                                                                                                                                                    \
					"font-weight: normal;"                                                                                                                                                        \
					"font-style: normal;"                                                                                                                                                         \
					"font-size: 17px;"                                                                                                                                                            \
					"line-height: 20px;"                                                                                                                                                          \
					"padding: 4px 4px 4px 4px;"                                                                                                                                                   \
					"margin: 0;"                                                                                                                                                                  \
					"text-align: center;"                                                                                                                                                         \
					"}"                                                                                                                                                                           \
					"#Editbox3:focus"                                                                                                                                                             \
					"{"                                                                                                                                                                           \
					"border-color: #66AFE9;"                                                                                                                                                      \
					"box-shadow: inset 0px 1px 1px rgba(0,0,0,0.075), 0px 0px 8px rgba(102,175,233,0.60);"                                                                                        \
					"outline: 0;"                                                                                                                                                                 \
					"}"                                                                                                                                                                           \
					"#Label5"                                                                                                                                                                     \
					"{"                                                                                                                                                                           \
					"border: 0px solid #000000;"                                                                                                                                                  \
					"border-radius: 4px;"                                                                                                                                                         \
					"background-color: transparent;"                                                                                                                                              \
					"background-image: none;"                                                                                                                                                     \
					"color: #000000;"                                                                                                                                                             \
					"font-family: \"Roboto\";"                                                                                                                                                    \
					"font-weight: normal;"                                                                                                                                                        \
					"font-style: normal;"                                                                                                                                                         \
					"font-size: 20px;"                                                                                                                                                            \
					"padding: 4px 4px 4px 4px;"                                                                                                                                                   \
					"margin: 0;"                                                                                                                                                                  \
					"text-align: left;"                                                                                                                                                           \
					"vertical-align: top;"                                                                                                                                                        \
					"}"                                                                                                                                                                           \
					"#Editbox4"                                                                                                                                                                   \
					"{"                                                                                                                                                                           \
					"border: 0px solid #DCDCDC;"                                                                                                                                                  \
					"border-radius: 0px;"                                                                                                                                                         \
					"background-color: #FBFBFB;"                                                                                                                                                  \
					"background-image: none;"                                                                                                                                                     \
					"color: #000000;"                                                                                                                                                             \
					"font-family: \"Roboto\";"                                                                                                                                                    \
					"font-weight: normal;"                                                                                                                                                        \
					"font-style: normal;"                                                                                                                                                         \
					"font-size: 17px;"                                                                                                                                                            \
					"line-height: 20px;"                                                                                                                                                          \
					"padding: 4px 4px 4px 4px;"                                                                                                                                                   \
					"margin: 0;"                                                                                                                                                                  \
					"text-align: center;"                                                                                                                                                         \
					"}"                                                                                                                                                                           \
					"#Editbox4:focus"                                                                                                                                                             \
					"{"                                                                                                                                                                           \
					"border-color: #66AFE9;"                                                                                                                                                      \
					"box-shadow: inset 0px 1px 1px rgba(0,0,0,0.075), 0px 0px 8px rgba(102,175,233,0.60);"                                                                                        \
					"outline: 0;"                                                                                                                                                                 \
					"}"                                                                                                                                                                           \
					"#wb_Heading2"                                                                                                                                                                \
					"{"                                                                                                                                                                           \
					"background-color: transparent;"                                                                                                                                              \
					"background-image: none;"                                                                                                                                                     \
					"border: 0px solid #000000;"                                                                                                                                                  \
					"border-radius: 0px;"                                                                                                                                                         \
					"margin: 0;"                                                                                                                                                                  \
					"padding: 0;"                                                                                                                                                                 \
					"text-align: center;"                                                                                                                                                         \
					"}"                                                                                                                                                                           \
					"#Heading2"                                                                                                                                                                   \
					"{"                                                                                                                                                                           \
					"color: #696969;"                                                                                                                                                             \
					"font-family: \"Roboto\";"                                                                                                                                                    \
					"font-weight: bold;"                                                                                                                                                          \
					"font-style: normal;"                                                                                                                                                         \
					"font-size: 21px;"                                                                                                                                                            \
					"margin: 0;"                                                                                                                                                                  \
					"text-align: center;"                                                                                                                                                         \
					"}"                                                                                                                                                                           \
					"#wb_FlipSwitch2"                                                                                                                                                             \
					"{"                                                                                                                                                                           \
					"margin: 0;"                                                                                                                                                                  \
					"}"                                                                                                                                                                           \
					"#FlipSwitch2"                                                                                                                                                                \
					"{"                                                                                                                                                                           \
					"display: none;"                                                                                                                                                              \
					"}"                                                                                                                                                                           \
					"#FlipSwitch2-label"                                                                                                                                                          \
					"{"                                                                                                                                                                           \
					"display: block;"                                                                                                                                                             \
					"overflow: hidden;"                                                                                                                                                           \
					"cursor: pointer;"                                                                                                                                                            \
					"border: 2px solid #636363;"                                                                                                                                                  \
					"border-radius: 30px;"                                                                                                                                                        \
					"box-sizing: border-box;"                                                                                                                                                     \
					"max-width: 100%;"                                                                                                                                                            \
					"height: 100%;"                                                                                                                                                               \
					"-webkit-transition: border-color 300ms ease-in 0s;"                                                                                                                          \
					"transition: border-color 300ms ease-in 0s;"                                                                                                                                  \
					"}"                                                                                                                                                                           \
					"#FlipSwitch2-inner"                                                                                                                                                          \
					"{"                                                                                                                                                                           \
					"box-sizing: border-box;"                                                                                                                                                     \
					"display: block;"                                                                                                                                                             \
					"width: 200%;"                                                                                                                                                                \
					"margin-left: -100%;"                                                                                                                                                         \
					"-webkit-transition: margin 300ms ease-in 0s;"                                                                                                                                \
					"transition: margin 300ms ease-in 0s;"                                                                                                                                        \
					"}"                                                                                                                                                                           \
					"#FlipSwitch2-inner:before, #FlipSwitch2-inner:after"                                                                                                                         \
					"{"                                                                                                                                                                           \
					"display: block;"                                                                                                                                                             \
					"float: left;"                                                                                                                                                                \
					"width: 50%;"                                                                                                                                                                 \
					"height: 30px;"                                                                                                                                                               \
					"padding: 0;"                                                                                                                                                                 \
					"line-height: 30px;"                                                                                                                                                          \
					"color: #000000;"                                                                                                                                                             \
					"font-family: Roboto;"                                                                                                                                                        \
					"font-weight: normal;"                                                                                                                                                        \
					"font-style: normal;"                                                                                                                                                         \
					"font-size: 13px;"                                                                                                                                                            \
					"box-sizing: border-box;"                                                                                                                                                     \
					"border-radius: 30px;"                                                                                                                                                        \
					"text-align: center;"                                                                                                                                                         \
					"}"                                                                                                                                                                           \
					"#FlipSwitch2-inner:before"                                                                                                                                                   \
					"{"                                                                                                                                                                           \
					"content: \"ON\";"                                                                                                                                                            \
					"padding-right: 30px;"                                                                                                                                                        \
					"background-color: #0275D8;"                                                                                                                                                  \
					"color: #FFFFFF;"                                                                                                                                                             \
					"border-radius: 30px 0 0 30px;"                                                                                                                                               \
					"}"                                                                                                                                                                           \
					"#FlipSwitch2-inner:after"                                                                                                                                                    \
					"{"                                                                                                                                                                           \
					"content: \"OFF\";"                                                                                                                                                           \
					"padding-left: 30px;"                                                                                                                                                         \
					"background-color: #E9E9E9;"                                                                                                                                                  \
					"color: #000000;"                                                                                                                                                             \
					"border-radius: 0 30px 30px 0;"                                                                                                                                               \
					"}"                                                                                                                                                                           \
					"#FlipSwitch2-switch"                                                                                                                                                         \
					"{"                                                                                                                                                                           \
					"display: block;"                                                                                                                                                             \
					"width: 30px;"                                                                                                                                                                \
					"margin: 0px;"                                                                                                                                                                \
					"background: #FFFFFF;"                                                                                                                                                        \
					"border: 2px solid #636363;"                                                                                                                                                  \
					"border-radius: 30px;"                                                                                                                                                        \
					"box-shadow: 0px 0px 5px rgba(0,0,0,0.30);"                                                                                                                                   \
					"position: absolute;"                                                                                                                                                         \
					"top: 2px;"                                                                                                                                                                   \
					"bottom: 2px;"                                                                                                                                                                \
					"right: 48px;"                                                                                                                                                                \
					"-webkit-transition: all 300ms ease-in 0s;"                                                                                                                                   \
					"transition: all 300ms ease-in 0s;"                                                                                                                                           \
					"box-sizing: border-box;"                                                                                                                                                     \
					"}"                                                                                                                                                                           \
					"#FlipSwitch2:checked + #FlipSwitch2-label"                                                                                                                                   \
					"{"                                                                                                                                                                           \
					"border-color: #636363;"                                                                                                                                                      \
					"}"                                                                                                                                                                           \
					"#FlipSwitch2:checked + #FlipSwitch2-label #FlipSwitch2-inner"                                                                                                                \
					"{"                                                                                                                                                                           \
					"margin-left: 0;"                                                                                                                                                             \
					"}"                                                                                                                                                                           \
					"#FlipSwitch2:checked + #FlipSwitch2-label #FlipSwitch2-switch"                                                                                                               \
					"{"                                                                                                                                                                           \
					"right: 2px;"                                                                                                                                                                 \
					"background: #FFFFFF;"                                                                                                                                                        \
					"border-color: #636363;"                                                                                                                                                      \
					"}"                                                                                                                                                                           \
					"#Label6"                                                                                                                                                                     \
					"{"                                                                                                                                                                           \
					"border: 0px solid #000000;"                                                                                                                                                  \
					"border-radius: 4px;"                                                                                                                                                         \
					"background-color: transparent;"                                                                                                                                              \
					"background-image: none;"                                                                                                                                                     \
					"color: #696969;"                                                                                                                                                             \
					"font-family: \"Roboto\";"                                                                                                                                                    \
					"font-weight: normal;"                                                                                                                                                        \
					"font-style: normal;"                                                                                                                                                         \
					"font-size: 20px;"                                                                                                                                                            \
					"padding: 4px 4px 4px 4px;"                                                                                                                                                   \
					"margin: 0;"                                                                                                                                                                  \
					"text-align: left;"                                                                                                                                                           \
					"vertical-align: top;"                                                                                                                                                        \
					"}"                                                                                                                                                                           \
					"#Label7"                                                                                                                                                                     \
					"{"                                                                                                                                                                           \
					"border: 0px solid #000000;"                                                                                                                                                  \
					"border-radius: 4px;"                                                                                                                                                         \
					"background-color: transparent;"                                                                                                                                              \
					"background-image: none;"                                                                                                                                                     \
					"color: #696969;"                                                                                                                                                             \
					"font-family: \"Roboto\";"                                                                                                                                                    \
					"font-weight: normal;"                                                                                                                                                        \
					"font-style: normal;"                                                                                                                                                         \
					"font-size: 20px;"                                                                                                                                                            \
					"padding: 4px 4px 4px 4px;"                                                                                                                                                   \
					"margin: 0;"                                                                                                                                                                  \
					"text-align: left;"                                                                                                                                                           \
					"vertical-align: top;"                                                                                                                                                        \
					"}"                                                                                                                                                                           \
					"#wb_FlipSwitch3"                                                                                                                                                             \
					"{"                                                                                                                                                                           \
					"margin: 0;"                                                                                                                                                                  \
					"}"                                                                                                                                                                           \
					"#FlipSwitch3"                                                                                                                                                                \
					"{"                                                                                                                                                                           \
					"display: none;"                                                                                                                                                              \
					"}"                                                                                                                                                                           \
					"#FlipSwitch3-label"                                                                                                                                                          \
					"{"                                                                                                                                                                           \
					"display: block;"                                                                                                                                                             \
					"overflow: hidden;"                                                                                                                                                           \
					"cursor: pointer;"                                                                                                                                                            \
					"border: 2px solid #636363;"                                                                                                                                                  \
					"border-radius: 30px;"                                                                                                                                                        \
					"box-sizing: border-box;"                                                                                                                                                     \
					"max-width: 100%;"                                                                                                                                                            \
					"height: 100%;"                                                                                                                                                               \
					"-webkit-transition: border-color 300ms ease-in 0s;"                                                                                                                          \
					"transition: border-color 300ms ease-in 0s;"                                                                                                                                  \
					"}"                                                                                                                                                                           \
					"#FlipSwitch3-inner"                                                                                                                                                          \
					"{"                                                                                                                                                                           \
					"box-sizing: border-box;"                                                                                                                                                     \
					"display: block;"                                                                                                                                                             \
					"width: 200%;"                                                                                                                                                                \
					"margin-left: -100%;"                                                                                                                                                         \
					"-webkit-transition: margin 300ms ease-in 0s;"                                                                                                                                \
					"transition: margin 300ms ease-in 0s;"                                                                                                                                        \
					"}"                                                                                                                                                                           \
					"#FlipSwitch3-inner:before, #FlipSwitch3-inner:after"                                                                                                                         \
					"{"                                                                                                                                                                           \
					"display: block;"                                                                                                                                                             \
					"float: left;"                                                                                                                                                                \
					"width: 50%;"                                                                                                                                                                 \
					"height: 30px;"                                                                                                                                                               \
					"padding: 0;"                                                                                                                                                                 \
					"line-height: 30px;"                                                                                                                                                          \
					"color: #000000;"                                                                                                                                                             \
					"font-family: Roboto;"                                                                                                                                                        \
					"font-weight: normal;"                                                                                                                                                        \
					"font-style: normal;"                                                                                                                                                         \
					"font-size: 13px;"                                                                                                                                                            \
					"box-sizing: border-box;"                                                                                                                                                     \
					"border-radius: 30px;"                                                                                                                                                        \
					"text-align: center;"                                                                                                                                                         \
					"}"                                                                                                                                                                           \
					"#FlipSwitch3-inner:before"                                                                                                                                                   \
					"{"                                                                                                                                                                           \
					"content: \"ON\";"                                                                                                                                                            \
					"padding-right: 30px;"                                                                                                                                                        \
					"background-color: #0275D8;"                                                                                                                                                  \
					"color: #FFFFFF;"                                                                                                                                                             \
					"border-radius: 30px 0 0 30px;"                                                                                                                                               \
					"}"                                                                                                                                                                           \
					"#FlipSwitch3-inner:after"                                                                                                                                                    \
					"{"                                                                                                                                                                           \
					"content: \"OFF\";"                                                                                                                                                           \
					"padding-left: 30px;"                                                                                                                                                         \
					"background-color: #E9E9E9;"                                                                                                                                                  \
					"color: #000000;"                                                                                                                                                             \
					"border-radius: 0 30px 30px 0;"                                                                                                                                               \
					"}"                                                                                                                                                                           \
					"#FlipSwitch3-switch"                                                                                                                                                         \
					"{"                                                                                                                                                                           \
					"display: block;"                                                                                                                                                             \
					"width: 30px;"                                                                                                                                                                \
					"margin: 0px;"                                                                                                                                                                \
					"background: #FFFFFF;"                                                                                                                                                        \
					"border: 2px solid #636363;"                                                                                                                                                  \
					"border-radius: 30px;"                                                                                                                                                        \
					"box-shadow: 0px 0px 5px rgba(0,0,0,0.30);"                                                                                                                                   \
					"position: absolute;"                                                                                                                                                         \
					"top: 2px;"                                                                                                                                                                   \
					"bottom: 2px;"                                                                                                                                                                \
					"right: 48px;"                                                                                                                                                                \
					"-webkit-transition: all 300ms ease-in 0s;"                                                                                                                                   \
					"transition: all 300ms ease-in 0s;"                                                                                                                                           \
					"box-sizing: border-box;"                                                                                                                                                     \
					"}"                                                                                                                                                                           \
					"#FlipSwitch3:checked + #FlipSwitch3-label"                                                                                                                                   \
					"{"                                                                                                                                                                           \
					"border-color: #636363;"                                                                                                                                                      \
					"}"                                                                                                                                                                           \
					"#FlipSwitch3:checked + #FlipSwitch3-label #FlipSwitch3-inner"                                                                                                                \
					"{"                                                                                                                                                                           \
					"margin-left: 0;"                                                                                                                                                             \
					"}"                                                                                                                                                                           \
					"#FlipSwitch3:checked + #FlipSwitch3-label #FlipSwitch3-switch"                                                                                                               \
					"{"                                                                                                                                                                           \
					"right: 2px;"                                                                                                                                                                 \
					"background: #FFFFFF;"                                                                                                                                                        \
					"border-color: #636363;"                                                                                                                                                      \
					"}"                                                                                                                                                                           \
					"#Label8"                                                                                                                                                                     \
					"{"                                                                                                                                                                           \
					"border: 0px solid #000000;"                                                                                                                                                  \
					"border-radius: 4px;"                                                                                                                                                         \
					"background-color: transparent;"                                                                                                                                              \
					"background-image: none;"                                                                                                                                                     \
					"color: #696969;"                                                                                                                                                             \
					"font-family: \"Roboto\";"                                                                                                                                                    \
					"font-weight: normal;"                                                                                                                                                        \
					"font-style: normal;"                                                                                                                                                         \
					"font-size: 20px;"                                                                                                                                                            \
					"padding: 4px 4px 4px 4px;"                                                                                                                                                   \
					"margin: 0;"                                                                                                                                                                  \
					"text-align: left;"                                                                                                                                                           \
					"vertical-align: top;"                                                                                                                                                        \
					"}"                                                                                                                                                                           \
					"#Combobox1"                                                                                                                                                                  \
					"{"                                                                                                                                                                           \
					"border: 2px solid #4F4F4F;"                                                                                                                                                  \
					"border-radius: 3px;"                                                                                                                                                         \
					"background-color: #FFFFFF;"                                                                                                                                                  \
					"background-image: none;"                                                                                                                                                     \
					"color: #000000;"                                                                                                                                                             \
					"font-family: \"Roboto\";"                                                                                                                                                    \
					"font-weight: normal;"                                                                                                                                                        \
					"font-style: normal;"                                                                                                                                                         \
					"font-size: 19px;"                                                                                                                                                            \
					"padding: 4px 4px 4px 4px;"                                                                                                                                                   \
					"margin: 0;"                                                                                                                                                                  \
					"box-sizing: border-box;"                                                                                                                                                     \
					"}"                                                                                                                                                                           \
					"#Label9"                                                                                                                                                                     \
					"{"                                                                                                                                                                           \
					"border: 0px solid #000000;"                                                                                                                                                  \
					"border-radius: 4px;"                                                                                                                                                         \
					"background-color: transparent;"                                                                                                                                              \
					"background-image: none;"                                                                                                                                                     \
					"color: #696969;"                                                                                                                                                             \
					"font-family: \"Roboto\";"                                                                                                                                                    \
					"font-weight: normal;"                                                                                                                                                        \
					"font-style: normal;"                                                                                                                                                         \
					"font-size: 20px;"                                                                                                                                                            \
					"padding: 4px 4px 4px 4px;"                                                                                                                                                   \
					"margin: 0;"                                                                                                                                                                  \
					"text-align: left;"                                                                                                                                                           \
					"vertical-align: top;"                                                                                                                                                        \
					"}"                                                                                                                                                                           \
					"#Editbox5"                                                                                                                                                                   \
					"{"                                                                                                                                                                           \
					"border: 2px solid #4F4F4F;"                                                                                                                                                  \
					"border-radius: 3px;"                                                                                                                                                         \
					"background-color: #FFFFFF;"                                                                                                                                                  \
					"background-image: none;"                                                                                                                                                     \
					"color: #000000;"                                                                                                                                                             \
					"font-family: \"Roboto\";"                                                                                                                                                    \
					"font-weight: normal;"                                                                                                                                                        \
					"font-style: normal;"                                                                                                                                                         \
					"font-size: 20px;"                                                                                                                                                            \
					"line-height: 25px;"                                                                                                                                                          \
					"padding: 4px 4px 4px 4px;"                                                                                                                                                   \
					"margin: 0;"                                                                                                                                                                  \
					"text-align: left;"                                                                                                                                                           \
					"}"                                                                                                                                                                           \
					"#Label10"                                                                                                                                                                    \
					"{"                                                                                                                                                                           \
					"border: 0px solid #000000;"                                                                                                                                                  \
					"border-radius: 4px;"                                                                                                                                                         \
					"background-color: transparent;"                                                                                                                                              \
					"background-image: none;"                                                                                                                                                     \
					"color: #696969;"                                                                                                                                                             \
					"font-family: \"Roboto\";"                                                                                                                                                    \
					"font-weight: normal;"                                                                                                                                                        \
					"font-style: normal;"                                                                                                                                                         \
					"font-size: 20px;"                                                                                                                                                            \
					"padding: 4px 4px 4px 4px;"                                                                                                                                                   \
					"margin: 0;"                                                                                                                                                                  \
					"text-align: left;"                                                                                                                                                           \
					"vertical-align: top;"                                                                                                                                                        \
					"}"                                                                                                                                                                           \
					"#Editbox6"                                                                                                                                                                   \
					"{"                                                                                                                                                                           \
					"border: 2px solid #4F4F4F;"                                                                                                                                                  \
					"border-radius: 3px;"                                                                                                                                                         \
					"background-color: #FFFFFF;"                                                                                                                                                  \
					"background-image: none;"                                                                                                                                                     \
					"color: #000000;"                                                                                                                                                             \
					"font-family: \"Roboto\";"                                                                                                                                                    \
					"font-weight: normal;"                                                                                                                                                        \
					"font-style: normal;"                                                                                                                                                         \
					"font-size: 20px;"                                                                                                                                                            \
					"line-height: 25px;"                                                                                                                                                          \
					"padding: 4px 4px 4px 4px;"                                                                                                                                                   \
					"margin: 0;"                                                                                                                                                                  \
					"text-align: left;"                                                                                                                                                           \
					"}"                                                                                                                                                                           \
					"#Label11"                                                                                                                                                                    \
					"{"                                                                                                                                                                           \
					"border: 0px solid #000000;"                                                                                                                                                  \
					"border-radius: 4px;"                                                                                                                                                         \
					"background-color: transparent;"                                                                                                                                              \
					"background-image: none;"                                                                                                                                                     \
					"color: #696969;"                                                                                                                                                             \
					"font-family: \"Roboto\";"                                                                                                                                                    \
					"font-weight: normal;"                                                                                                                                                        \
					"font-style: normal;"                                                                                                                                                         \
					"font-size: 20px;"                                                                                                                                                            \
					"padding: 4px 4px 4px 4px;"                                                                                                                                                   \
					"margin: 0;"                                                                                                                                                                  \
					"text-align: left;"                                                                                                                                                           \
					"vertical-align: top;"                                                                                                                                                        \
					"}"                                                                                                                                                                           \
					"#Editbox7"                                                                                                                                                                   \
					"{"                                                                                                                                                                           \
					"border: 2px solid #4F4F4F;"                                                                                                                                                  \
					"border-radius: 3px;"                                                                                                                                                         \
					"background-color: #FFFFFF;"                                                                                                                                                  \
					"background-image: none;"                                                                                                                                                     \
					"color: #000000;"                                                                                                                                                             \
					"font-family: \"Roboto\";"                                                                                                                                                    \
					"font-weight: normal;"                                                                                                                                                        \
					"font-style: normal;"                                                                                                                                                         \
					"font-size: 20px;"                                                                                                                                                            \
					"line-height: 25px;"                                                                                                                                                          \
					"padding: 4px 4px 4px 4px;"                                                                                                                                                   \
					"margin: 0;"                                                                                                                                                                  \
					"text-align: left;"                                                                                                                                                           \
					"}"                                                                                                                                                                           \
					"#Label12"                                                                                                                                                                    \
					"{"                                                                                                                                                                           \
					"border: 0px solid #000000;"                                                                                                                                                  \
					"border-radius: 4px;"                                                                                                                                                         \
					"background-color: transparent;"                                                                                                                                              \
					"background-image: none;"                                                                                                                                                     \
					"color: #696969;"                                                                                                                                                             \
					"font-family: \"Roboto\";"                                                                                                                                                    \
					"font-weight: normal;"                                                                                                                                                        \
					"font-style: normal;"                                                                                                                                                         \
					"font-size: 20px;"                                                                                                                                                            \
					"padding: 4px 4px 4px 4px;"                                                                                                                                                   \
					"margin: 0;"                                                                                                                                                                  \
					"text-align: left;"                                                                                                                                                           \
					"vertical-align: top;"                                                                                                                                                        \
					"}"                                                                                                                                                                           \
					"#Editbox8"                                                                                                                                                                   \
					"{"                                                                                                                                                                           \
					"border: 2px solid #4F4F4F;"                                                                                                                                                  \
					"border-radius: 3px;"                                                                                                                                                         \
					"background-color: #FFFFFF;"                                                                                                                                                  \
					"background-image: none;"                                                                                                                                                     \
					"color: #000000;"                                                                                                                                                             \
					"font-family: \"Roboto\";"                                                                                                                                                    \
					"font-weight: normal;"                                                                                                                                                        \
					"font-style: normal;"                                                                                                                                                         \
					"font-size: 20px;"                                                                                                                                                            \
					"line-height: 25px;"                                                                                                                                                          \
					"padding: 4px 4px 4px 4px;"                                                                                                                                                   \
					"margin: 0;"                                                                                                                                                                  \
					"text-align: left;"                                                                                                                                                           \
					"}"                                                                                                                                                                           \
					"#Label13"                                                                                                                                                                    \
					"{"                                                                                                                                                                           \
					"border: 0px solid #000000;"                                                                                                                                                  \
					"border-radius: 4px;"                                                                                                                                                         \
					"background-color: transparent;"                                                                                                                                              \
					"background-image: none;"                                                                                                                                                     \
					"color: #696969;"                                                                                                                                                             \
					"font-family: \"Roboto\";"                                                                                                                                                    \
					"font-weight: normal;"                                                                                                                                                        \
					"font-style: normal;"                                                                                                                                                         \
					"font-size: 20px;"                                                                                                                                                            \
					"padding: 4px 4px 4px 4px;"                                                                                                                                                   \
					"margin: 0;"                                                                                                                                                                  \
					"text-align: left;"                                                                                                                                                           \
					"vertical-align: top;"                                                                                                                                                        \
					"}"                                                                                                                                                                           \
					"#Editbox9"                                                                                                                                                                   \
					"{"                                                                                                                                                                           \
					"border: 2px solid #4F4F4F;"                                                                                                                                                  \
					"border-radius: 3px;"                                                                                                                                                         \
					"background-color: #FFFFFF;"                                                                                                                                                  \
					"background-image: none;"                                                                                                                                                     \
					"color: #000000;"                                                                                                                                                             \
					"font-family: \"Roboto\";"                                                                                                                                                    \
					"font-weight: normal;"                                                                                                                                                        \
					"font-style: normal;"                                                                                                                                                         \
					"font-size: 20px;"                                                                                                                                                            \
					"line-height: 25px;"                                                                                                                                                          \
					"padding: 4px 4px 4px 4px;"                                                                                                                                                   \
					"margin: 0;"                                                                                                                                                                  \
					"text-align: left;"                                                                                                                                                           \
					"}"                                                                                                                                                                           \
					"#Label14"                                                                                                                                                                    \
					"{"                                                                                                                                                                           \
					"border: 0px solid #000000;"                                                                                                                                                  \
					"border-radius: 4px;"                                                                                                                                                         \
					"background-color: transparent;"                                                                                                                                              \
					"background-image: none;"                                                                                                                                                     \
					"color: #696969;"                                                                                                                                                             \
					"font-family: \"Roboto\";"                                                                                                                                                    \
					"font-weight: normal;"                                                                                                                                                        \
					"font-style: normal;"                                                                                                                                                         \
					"font-size: 20px;"                                                                                                                                                            \
					"padding: 4px 4px 4px 4px;"                                                                                                                                                   \
					"margin: 0;"                                                                                                                                                                  \
					"text-align: left;"                                                                                                                                                           \
					"vertical-align: top;"                                                                                                                                                        \
					"}"                                                                                                                                                                           \
					"#Editbox10"                                                                                                                                                                  \
					"{"                                                                                                                                                                           \
					"border: 2px solid #4F4F4F;"                                                                                                                                                  \
					"border-radius: 3px;"                                                                                                                                                         \
					"background-color: #FFFFFF;"                                                                                                                                                  \
					"background-image: none;"                                                                                                                                                     \
					"color: #000000;"                                                                                                                                                             \
					"font-family: \"Roboto\";"                                                                                                                                                    \
					"font-weight: normal;"                                                                                                                                                        \
					"font-style: normal;"                                                                                                                                                         \
					"font-size: 20px;"                                                                                                                                                            \
					"line-height: 25px;"                                                                                                                                                          \
					"padding: 4px 4px 4px 4px;"                                                                                                                                                   \
					"margin: 0;"                                                                                                                                                                  \
					"text-align: left;"                                                                                                                                                           \
					"}"                                                                                                                                                                           \
					"#Label15"                                                                                                                                                                    \
					"{"                                                                                                                                                                           \
					"border: 0px solid #000000;"                                                                                                                                                  \
					"border-radius: 4px;"                                                                                                                                                         \
					"background-color: transparent;"                                                                                                                                              \
					"background-image: none;"                                                                                                                                                     \
					"color: #696969;"                                                                                                                                                             \
					"font-family: \"Roboto\";"                                                                                                                                                    \
					"font-weight: normal;"                                                                                                                                                        \
					"font-style: normal;"                                                                                                                                                         \
					"font-size: 20px;"                                                                                                                                                            \
					"padding: 4px 4px 4px 4px;"                                                                                                                                                   \
					"margin: 0;"                                                                                                                                                                  \
					"text-align: left;"                                                                                                                                                           \
					"vertical-align: top;"                                                                                                                                                        \
					"}"                                                                                                                                                                           \
					"#Editbox11"                                                                                                                                                                  \
					"{"                                                                                                                                                                           \
					"border: 2px solid #4F4F4F;"                                                                                                                                                  \
					"border-radius: 3px;"                                                                                                                                                         \
					"background-color: #FFFFFF;"                                                                                                                                                  \
					"background-image: none;"                                                                                                                                                     \
					"color: #000000;"                                                                                                                                                             \
					"font-family: \"Roboto\";"                                                                                                                                                    \
					"font-weight: normal;"                                                                                                                                                        \
					"font-style: normal;"                                                                                                                                                         \
					"font-size: 20px;"                                                                                                                                                            \
					"line-height: 25px;"                                                                                                                                                          \
					"padding: 4px 4px 4px 4px;"                                                                                                                                                   \
					"margin: 0;"                                                                                                                                                                  \
					"text-align: left;"                                                                                                                                                           \
					"}"                                                                                                                                                                           \
					"#Label16"                                                                                                                                                                    \
					"{"                                                                                                                                                                           \
					"border: 0px solid #000000;"                                                                                                                                                  \
					"border-radius: 4px;"                                                                                                                                                         \
					"background-color: transparent;"                                                                                                                                              \
					"background-image: none;"                                                                                                                                                     \
					"color: #696969;"                                                                                                                                                             \
					"font-family: \"Roboto\";"                                                                                                                                                    \
					"font-weight: normal;"                                                                                                                                                        \
					"font-style: normal;"                                                                                                                                                         \
					"font-size: 20px;"                                                                                                                                                            \
					"padding: 4px 4px 4px 4px;"                                                                                                                                                   \
					"margin: 0;"                                                                                                                                                                  \
					"text-align: left;"                                                                                                                                                           \
					"vertical-align: top;"                                                                                                                                                        \
					"}"                                                                                                                                                                           \
					"#Editbox12"                                                                                                                                                                  \
					"{"                                                                                                                                                                           \
					"border: 2px solid #4F4F4F;"                                                                                                                                                  \
					"border-radius: 3px;"                                                                                                                                                         \
					"background-color: #FFFFFF;"                                                                                                                                                  \
					"background-image: none;"                                                                                                                                                     \
					"color: #000000;"                                                                                                                                                             \
					"font-family: \"Roboto\";"                                                                                                                                                    \
					"font-weight: normal;"                                                                                                                                                        \
					"font-style: normal;"                                                                                                                                                         \
					"font-size: 20px;"                                                                                                                                                            \
					"line-height: 25px;"                                                                                                                                                          \
					"padding: 4px 4px 4px 4px;"                                                                                                                                                   \
					"margin: 0;"                                                                                                                                                                  \
					"text-align: left;"                                                                                                                                                           \
					"}"                                                                                                                                                                           \
					"#Label17"                                                                                                                                                                    \
					"{"                                                                                                                                                                           \
					"border: 0px solid #000000;"                                                                                                                                                  \
					"border-radius: 4px;"                                                                                                                                                         \
					"background-color: transparent;"                                                                                                                                              \
					"background-image: none;"                                                                                                                                                     \
					"color: #696969;"                                                                                                                                                             \
					"font-family: \"Roboto\";"                                                                                                                                                    \
					"font-weight: normal;"                                                                                                                                                        \
					"font-style: normal;"                                                                                                                                                         \
					"font-size: 20px;"                                                                                                                                                            \
					"padding: 4px 4px 4px 4px;"                                                                                                                                                   \
					"margin: 0;"                                                                                                                                                                  \
					"text-align: left;"                                                                                                                                                           \
					"vertical-align: top;"                                                                                                                                                        \
					"}"                                                                                                                                                                           \
					"#Editbox13"                                                                                                                                                                  \
					"{"                                                                                                                                                                           \
					"border: 2px solid #4F4F4F;"                                                                                                                                                  \
					"border-radius: 3px;"                                                                                                                                                         \
					"background-color: #FFFFFF;"                                                                                                                                                  \
					"background-image: none;"                                                                                                                                                     \
					"color: #000000;"                                                                                                                                                             \
					"font-family: \"Roboto\";"                                                                                                                                                    \
					"font-weight: normal;"                                                                                                                                                        \
					"font-style: normal;"                                                                                                                                                         \
					"font-size: 20px;"                                                                                                                                                            \
					"line-height: 25px;"                                                                                                                                                          \
					"padding: 4px 4px 4px 4px;"                                                                                                                                                   \
					"margin: 0;"                                                                                                                                                                  \
					"text-align: left;"                                                                                                                                                           \
					"}"                                                                                                                                                                           \
					"#Label18"                                                                                                                                                                    \
					"{"                                                                                                                                                                           \
					"border: 0px solid #000000;"                                                                                                                                                  \
					"border-radius: 4px;"                                                                                                                                                         \
					"background-color: transparent;"                                                                                                                                              \
					"background-image: none;"                                                                                                                                                     \
					"color: #696969;"                                                                                                                                                             \
					"font-family: \"Roboto\";"                                                                                                                                                    \
					"font-weight: normal;"                                                                                                                                                        \
					"font-style: normal;"                                                                                                                                                         \
					"font-size: 20px;"                                                                                                                                                            \
					"padding: 4px 4px 4px 4px;"                                                                                                                                                   \
					"margin: 0;"                                                                                                                                                                  \
					"text-align: left;"                                                                                                                                                           \
					"vertical-align: top;"                                                                                                                                                        \
					"}"                                                                                                                                                                           \
					"#Editbox14"                                                                                                                                                                  \
					"{"                                                                                                                                                                           \
					"border: 2px solid #4F4F4F;"                                                                                                                                                  \
					"border-radius: 3px;"                                                                                                                                                         \
					"background-color: #FFFFFF;"                                                                                                                                                  \
					"background-image: none;"                                                                                                                                                     \
					"color: #000000;"                                                                                                                                                             \
					"font-family: \"Roboto\";"                                                                                                                                                    \
					"font-weight: normal;"                                                                                                                                                        \
					"font-style: normal;"                                                                                                                                                         \
					"font-size: 20px;"                                                                                                                                                            \
					"line-height: 25px;"                                                                                                                                                          \
					"padding: 4px 4px 4px 4px;"                                                                                                                                                   \
					"margin: 0;"                                                                                                                                                                  \
					"text-align: left;"                                                                                                                                                           \
					"}"                                                                                                                                                                           \
					"#Label19"                                                                                                                                                                    \
					"{"                                                                                                                                                                           \
					"border: 0px solid #000000;"                                                                                                                                                  \
					"border-radius: 4px;"                                                                                                                                                         \
					"background-color: transparent;"                                                                                                                                              \
					"background-image: none;"                                                                                                                                                     \
					"color: #696969;"                                                                                                                                                             \
					"font-family: \"Roboto\";"                                                                                                                                                    \
					"font-weight: normal;"                                                                                                                                                        \
					"font-style: normal;"                                                                                                                                                         \
					"font-size: 20px;"                                                                                                                                                            \
					"padding: 4px 4px 4px 4px;"                                                                                                                                                   \
					"margin: 0;"                                                                                                                                                                  \
					"text-align: left;"                                                                                                                                                           \
					"vertical-align: top;"                                                                                                                                                        \
					"}"                                                                                                                                                                           \
					"#Editbox15"                                                                                                                                                                  \
					"{"                                                                                                                                                                           \
					"border: 2px solid #4F4F4F;"                                                                                                                                                  \
					"border-radius: 3px;"                                                                                                                                                         \
					"background-color: #FFFFFF;"                                                                                                                                                  \
					"background-image: none;"                                                                                                                                                     \
					"color: #000000;"                                                                                                                                                             \
					"font-family: \"Roboto\";"                                                                                                                                                    \
					"font-weight: normal;"                                                                                                                                                        \
					"font-style: normal;"                                                                                                                                                         \
					"font-size: 20px;"                                                                                                                                                            \
					"line-height: 25px;"                                                                                                                                                          \
					"padding: 4px 4px 4px 4px;"                                                                                                                                                   \
					"margin: 0;"                                                                                                                                                                  \
					"text-align: left;"                                                                                                                                                           \
					"}"                                                                                                                                                                           \
					"#Label20"                                                                                                                                                                    \
					"{"                                                                                                                                                                           \
					"border: 0px solid #000000;"                                                                                                                                                  \
					"border-radius: 4px;"                                                                                                                                                         \
					"background-color: transparent;"                                                                                                                                              \
					"background-image: none;"                                                                                                                                                     \
					"color: #696969;"                                                                                                                                                             \
					"font-family: \"Roboto\";"                                                                                                                                                    \
					"font-weight: normal;"                                                                                                                                                        \
					"font-style: normal;"                                                                                                                                                         \
					"font-size: 20px;"                                                                                                                                                            \
					"padding: 4px 4px 4px 4px;"                                                                                                                                                   \
					"margin: 0;"                                                                                                                                                                  \
					"text-align: left;"                                                                                                                                                           \
					"vertical-align: top;"                                                                                                                                                        \
					"}"                                                                                                                                                                           \
					"#Label21"                                                                                                                                                                    \
					"{"                                                                                                                                                                           \
					"border: 0px solid #000000;"                                                                                                                                                  \
					"border-radius: 4px;"                                                                                                                                                         \
					"background-color: transparent;"                                                                                                                                              \
					"background-image: none;"                                                                                                                                                     \
					"color: #696969;"                                                                                                                                                             \
					"font-family: \"Roboto\";"                                                                                                                                                    \
					"font-weight: normal;"                                                                                                                                                        \
					"font-style: normal;"                                                                                                                                                         \
					"font-size: 20px;"                                                                                                                                                            \
					"padding: 4px 4px 4px 4px;"                                                                                                                                                   \
					"margin: 0;"                                                                                                                                                                  \
					"text-align: left;"                                                                                                                                                           \
					"vertical-align: top;"                                                                                                                                                        \
					"}"                                                                                                                                                                           \
					"#Button5"                                                                                                                                                                    \
					"{"                                                                                                                                                                           \
					"border-top-width: 2px;"                                                                                                                                                      \
					"border-right-width: 4px;"                                                                                                                                                    \
					"border-bottom-width: 5px;"                                                                                                                                                   \
					"border-left-width: 2px;"                                                                                                                                                     \
					"border-top-style: solid;"                                                                                                                                                    \
					"border-right-style: ridge;"                                                                                                                                                  \
					"border-bottom-style: ridge;"                                                                                                                                                 \
					"border-left-style: ridge;"                                                                                                                                                   \
					"border-top-color: #000000;"                                                                                                                                                  \
					"border-right-color: #000000;"                                                                                                                                                \
					"border-bottom-color: #000000;"                                                                                                                                               \
					"border-left-color: #000000;"                                                                                                                                                 \
					"border-top-left-radius: 0px;"                                                                                                                                                \
					"border-top-right-radius: 3px;"                                                                                                                                               \
					"border-bottom-right-radius: 6px;"                                                                                                                                            \
					"border-bottom-left-radius: 1px;"                                                                                                                                             \
					"background-color: #0078FF;"                                                                                                                                                  \
					"background-image: none;"                                                                                                                                                     \
					"color: #FFFFFF;"                                                                                                                                                             \
					"font-family: Roboto;"                                                                                                                                                        \
					"font-weight: bold;"                                                                                                                                                          \
					"font-style: normal;"                                                                                                                                                         \
					"font-size: 20px;"                                                                                                                                                            \
					"padding: 1px 6px 1px 6px;"                                                                                                                                                   \
					"text-align: center;"                                                                                                                                                         \
					"-webkit-appearance: none;"                                                                                                                                                   \
					"margin: 0;"                                                                                                                                                                  \
					"}"                                                                                                                                                                           \
					"#Button6"                                                                                                                                                                    \
					"{"                                                                                                                                                                           \
					"border-top-width: 2px;"                                                                                                                                                      \
					"border-right-width: 4px;"                                                                                                                                                    \
					"border-bottom-width: 5px;"                                                                                                                                                   \
					"border-left-width: 2px;"                                                                                                                                                     \
					"border-top-style: solid;"                                                                                                                                                    \
					"border-right-style: ridge;"                                                                                                                                                  \
					"border-bottom-style: ridge;"                                                                                                                                                 \
					"border-left-style: ridge;"                                                                                                                                                   \
					"border-top-color: #000000;"                                                                                                                                                  \
					"border-right-color: #000000;"                                                                                                                                                \
					"border-bottom-color: #000000;"                                                                                                                                               \
					"border-left-color: #000000;"                                                                                                                                                 \
					"border-top-left-radius: 0px;"                                                                                                                                                \
					"border-top-right-radius: 3px;"                                                                                                                                               \
					"border-bottom-right-radius: 6px;"                                                                                                                                            \
					"border-bottom-left-radius: 1px;"                                                                                                                                             \
					"background-color: #0078FF;"                                                                                                                                                  \
					"background-image: none;"                                                                                                                                                     \
					"color: #FFFFFF;"                                                                                                                                                             \
					"font-family: Roboto;"                                                                                                                                                        \
					"font-weight: bold;"                                                                                                                                                          \
					"font-style: normal;"                                                                                                                                                         \
					"font-size: 20px;"                                                                                                                                                            \
					"padding: 1px 6px 1px 6px;"                                                                                                                                                   \
					"text-align: center;"                                                                                                                                                         \
					"-webkit-appearance: none;"                                                                                                                                                   \
					"margin: 0;"                                                                                                                                                                  \
					"}"                                                                                                                                                                           \
					".navbar {"
					"	overflow: hidden;"
					"	background-color: #333;"
					"}"
					".navbar a {"
					"	float: left;"
					"	display: block;"
					"	color: white;"
					"	text-align: center;"
					"   font-size : large;"
					"	padding: 14px 20px;"
					"	text-decoration: none;"
					"}"
					".navbar a:hover {"
					"	background-color: #ddd;"
					"	color: black;"
					"}"
					"</style>"                                                                                                                                                                    \
					"</head>"                                                                                                                                                                     \
					"<body>"                                                                                                                                                                      \
					"<div class=\"navbar\">"\
					"    <a href=\"/main.html\">Home</a>"\
					"    <a href=\"/networksettings.html\">Network Settings</a>"\
					"    <a href=\"/timesyncpage\">Time Sync</a>"\
					"    <a href=\"/update_firmware.html\">Update Firmware</a>"\
					"</div>"\
					"<div style = \"position:relative;\">"
					"<div id=\"wb_Heading4\" style=\"position:absolute;left:160px;top:13px;width:500px;height:50px;z-index:51;\">"                                                                \
					"<h1 id=\"Heading4\">Motion Control Pro Management </h1></div>"                                                                                                               \
					"<hr id=\"Line1\" style=\"position:absolute;left:165px;top:58px;width:1164px;z-index:52;\">"                                                                                  \
					"<div id=\"wb_Form1\" style=\"position:absolute;left:155px;top:429px;width:562px;height:462px;z-index:53;\">"                                                                 \
					"<form name=\"Form1\" method=\"get\" action=\"/CONTROL\" enctype=\"multipart/form-data\" id=\"Form1\" onsubmit=\"document.getElementById('Form1').submit();return false;\">"  \
					"<div id=\"wb_Heading1\" style=\"position:absolute;left:165px;top:15px;width:253px;height:53px;z-index:33;\">"                                                                \
					"<h1 id=\"Heading1\">Control Remotely</h1></div>"                                                                                                                             \
					"</select>"                                                                                                                                                                   \
					"<input type=\"button\" id=\"Button1\"  \" name=\"A\" value=\"USB LOG\" style=\"position:absolute;left:152px;top:60px;width:253px;height:40px;z-index:35;\">"                 \
					"<input type=\"button\" id=\"Button2\"  \" name=\"A\" value=\"USB PROGRAM\" style=\"position:absolute;left:152px;top:130px;width:253px;height:40px;z-index:36;\">"            \
					"<input type=\"button\" id=\"Button3\"  \" name=\"A\" value=\"TEST ON\" style=\"position:absolute;left:152px;top:200px;width:253px;height:40px;z-index:37;\">"                \
					"<input type=\"button\" id=\"Button4\"  \" name=\"A\" value=\"TEST OFF\" style=\"position:absolute;left:152px;top:270px;width:253px;height:40px;z-index:38;\">"               \
					"<input type=\"button\" id=\"Button5\"   \" name=\"A\" value=\"LEARN ON\" style=\"position:absolute;left:152px;top:340px;width:253px;height:40px;z-index:39;\">"              \
					"<input type=\"button\" id=\"Button6\"   \" name=\"A\" value=\"LEARN OFF\" style=\"position:absolute;left:152px;top:410px;width:253px;height:40px;z-index:40;\">"             \
					"</form>"                                                                                                                                                                     \
					"</div>"                                                                                                                                                                      \
					"<div id=\"wb_Form2\" style=\"position:absolute;left:155px;top:86px;width:562px;height:308px;z-index:54;\">"                                                                  \
					"<form name=\"Form1\" method=\"get\" action=\"/FIRMWARE\" enctype=\"multipart/form-data\" id=\"Form2\" onsubmit=\"document.getElementById('Form2').submit();return false;\">" \
					"<div id=\"wb_Heading1\" style=\"position:absolute;left:186px;top:21px;width:190px;height:33px;z-index:40;\">"                                                                \
					"<h1 id=\"Heading1\">Measurements</h1></div>"                                                                                                                                 \
					"<p id=\"datetime\"></p>"                                                                                                                                                     \
					"<script>"                                                                                                                                                                    \
					"var now = new Date();"                                                                                                                                                       \
					"var datetime = now.toLocaleString();"                                                                                                                                        \
					"document.getElementById(\"datetime\").innerHTML = datetime;"                                                                                                                 \
					"</script>";
const char* firmware_page = \
"<!DOCTYPE html>\n"
"<html lang = \"en\">\n"
"    <head>\n"
"		<meta charset=\"UTF-8\">\n"
"		    <meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\">\n"
		"<style>\n"
		        "body { color: #dddddd; background-color: #333333; margin: 0; }\n"
		        "#file-input { display: none; }"
		        ".custom-file-label { display: inline-block; padding: 10px 20px; background-color: #007BFF; color: white; font-size: 16px; cursor: pointer; border-radius: 5px; border: none; transition: background-color 0.3s ease; }\n"
		        ".custom-file-label:hover { background-color: #0056b3; }\n"
		        "#upload-button { display: inline-block; padding: 10px 20px; background-color: #007BFF; color: white; font-size: 16px; cursor: pointer; border-radius: 5px; border: none; transition: background-color 0.3s ease; }\n"
		        "#upload-button:hover { background-color: #0056b3; }\n"
		        "#upload-button:active { background-color: #b30077; }\n"
		        "hr { border-color: blueviolet; }\n"
		".navbar {"
							"	overflow: hidden;"
							"	background-color: #333;"
							"}"
							".navbar a {"
							"	float: left;"
							"	display: block;"
							"	color: white;"
							"	text-align: center;"
							"   font-size : large;"
							"	padding: 14px 20px;"
							"	text-decoration: none;"
							"}"
							".navbar a:hover {"
							"	background-color: #ddd;"
							"	color: black;"
							"}"
		        "</style>\n"
"        <title>Firmware Uploader</title>\n"
"    </head>\n"
"    <body onload=\"passwordCheck()\">\n"
		"<div class=\"navbar\">"\
		"    <a href=\"/main.html\">Home</a>"\
		"    <a href=\"/networksettings.html\">Network Settings</a>"\
		"    <a href=\"/timesyncpage\">Time Sync</a>"\
		"    <a href=\"/update_firmware.html\">Update Firmware</a>"\
		"</div>"\
"		<h1>Firmware Uploader</h1>\n"
"        <form action=\"/firmware\" id=\"upload-form\" enctype=\"multipart/form-data\">\n"
"			 <h2>Select firmware file (*.bin)</h2>\n"
"			 <hr>\n"
"            <p>\n"
"                <input type=\"file\" id=\"file-input\" name=\"file\" accept=\".bin\" required onchange=\"enableButton()\">\n"
"				 <label for=\"file-input\" class=\"custom-file-label\">Choose File</label>\n"
"                <button type=\"button\" id=\"upload-button\" onclick=\"startUpload()\" style=\"display:none;\">Upload</button>\n"
"                <span id=\"alarm\" readonly></span>\n"
"            </p>\n"
"            <p style=\"display:none;\" id=\"progress-bar\">\n"
"                Loaded <span id=\"current-chunk\" readonly>N</span>\n"
"                part of <span id=\"total-chunks\" readonly>N</span>\n"
"                <span style=\"display:none;\" id=\"text-block\">. &nbsp; File uploaded successfully.</span>\n"
"            </p>\n"
"        </form>\n"
"        <script>\n"
"            const fileInput = document.getElementById('file-input');\n"
"            const uploadButton = document.getElementById('upload-button');\n"
"            const currentChunkLabel = document.getElementById('current-chunk');\n"
"            const totalChunksLabel = document.getElementById('total-chunks');\n"
"            const alarmLabel = document.getElementById('alarm');\n"
"            const textBlock = document.getElementById('text-block');\n"
"            const progressBar = document.getElementById('progress-bar');\n"
"            async function enableButton() {\n"
"                progressBar.style.display = 'inline-block';\n"
"                uploadButton.style.display = 'inline-block';\n"
"            }\n"
"            async function startUpload() {\n"
"                uploadButton.disabled = true;\n"
"                if (fileInput.files.length > 0) {\n"
"                    const file = fileInput.files[0];\n"
"                    const chunkSize = 512;\n"
"                    const totalChunks = Math.ceil(file.size / chunkSize);\n"
"                    let currentChunk = 0;\n"
"                    let errorCounter = 0;\n"
"                    async function uploadChunk() {\n"
"                        const start = currentChunk * chunkSize;\n"
"                        const end = Math.min(start + chunkSize, file.size);\n"
"                        const chunkData = file.slice(start, end);\n"
"                        const reader = new FileReader();\n"
"                        reader.onload = async function(event) {\n"
"                            const arrayBuffer = event.target.result;\n"
"                            const uint8Array = new Uint8Array(arrayBuffer);\n"
"					         const base64String = btoa(String.fromCharCode(...uint8Array));"
"                            const crc = crc32(uint8Array);\n"
"                            const formData = new FormData();\n"
"                            formData.append('fileChunk', base64String);\n"
"							 formData.append('chunkInfo', `currentChunk_${currentChunk}_totalSize_${file.size}_endChunk`);\n"
"                            formData.append('crc32', crc.toString());\n"
"                            try {\n"
"                                const response = await fetch('/firmware.cgi', {\n"
"                                    method: 'POST',\n"
"                                    body: formData\n"
"                                });\n"
"                                if (!response.ok) {\n"
"                                    throw new Error('Network response was not ok');\n"
"                                }\n"
"                                currentChunkLabel.textContent = currentChunk + 1;\n"
"                                totalChunksLabel.textContent = totalChunks;\n"
"                                currentChunk++;\n"
"                                errorCounter=0;\n"
"                            } catch (error) {\n"
"                                errorCounter++;\n"
"                                if (errorCounter > 10) {\n"
"                                    alarmLabel.textContent = 'File upload error, please try again';\n"
"                                    return;\n"
"                                }\n"
"                            }\n"
"                            if (currentChunk < totalChunks) {\n"
"                                uploadChunk();\n"
"                            } else {\n"
"                                uploadButton.disabled = false;\n"
"                                textBlock.style.display = 'inline-block';\n"
"                            }\n"
"                        };\n"
"                        reader.readAsArrayBuffer(chunkData);\n"
"                    }\n"
"                    uploadChunk();\n"
"                }\n"
"            }\n"
"            function crc32(array) {\n"
"                let crcTable = [];\n"
"                let crc;\n"
"                for (let i = 0; i < 256; i++) {\n"
"                    crc = i;\n"
"                    for (let j = 8; j > 0; j--) {\n"
"                        if ((crc & 1) === 1) {\n"
"                            crc = (crc >>> 1) ^ 0xEDB88320;\n"
"                        } else {\n"
"                            crc >>>= 1;\n"
"                        }\n"
"                    }\n"
"                    crcTable[i] = crc;\n"
"                }\n"
"                crc = 0xFFFFFFFF;\n"
"                for (let i = 0; i < array.length; i++) {\n"
"                    const byte = array[i];\n"
"                    crc = (crc >>> 8) ^ crcTable[(crc ^ byte) & 0xFF];\n"
"                }\n"
"                return (crc ^ 0xFFFFFFFF) >>> 0;\n"
"            }\n"
"        </script>\n"
"    </body>\n"
"</html>\n";

const char* setting_page = "<!DOCTYPE html>\
		<html lang=\"en\">\
		<head>\
    	<meta charset=\"UTF-8\">\
    	<meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\">\
    	<title>Network Settings</title>\
    	<style>\
        	body {\
            	font-family: 'Arial', sans-serif;\
            	background-color: #f0f0f0;\
            	margin: 0;\
            	display: flex;\
            	flex-direction: column;\
            	height: 100vh;\
        	}\
        	h1 {\
            	color: #333;\
        	}\
        	table {\
            	width: 50%%;\
            	border-collapse: collapse;\
            	margin: 20px 0;\
            	background-color: #fff;\
            	box-shadow: 0 0 10px rgba(0, 0, 0, 0.1);\
            	border-radius: 8px;\
            	overflow: hidden;\
        	}\
        	th, td {\
            	border: 1px solid #dddddd;\
            	text-align: left;\
            	padding: 12px;\
        	}\
        	th {\
            	background-color: #6c757d;\
            	color: white;\
        	}\
        	.button-container {\
            	text-align: center;\
            	margin-top: 20px;\
        	}\
        	.action-button {\
            	padding: 10px;\
            	background-color: #6c757d;\
            	color: white;\
            	border: none;\
            	border-radius: 5px;\
            	cursor: pointer;\
        	}"
		".navbar {"
					"	overflow: hidden;"
					"	background-color: #333;"
					"}"
					".navbar a {"
					"	float: left;"
					"	display: block;"
					"	color: white;"
					"	text-align: center;"
					"   font-size : large;"
					"	padding: 14px 20px;"
					"	text-decoration: none;"
					"}"
					".navbar a:hover {"
					"	background-color: #ddd;"
					"	color: black;"
					"}"
    	"</style>\
	</head>\
	<body>"
		"<div class=\"navbar\">"\
		"    <a href=\"/main.html\">Home</a>"\
		"    <a href=\"/networksettings.html\">Network Settings</a>"\
		"    <a href=\"/timesyncpage\">Time Sync</a>"\
		"    <a href=\"/update_firmware.html\">Update Firmware</a>"\
		"</div>"\
    	"<h1>Network Settings</h1>\
    	<form action=\"/networksettings.html\" method=\"get\">\
    	<table>\
        <tr>\
            <th>DHCP or STATIC</th>\
    		<td align=\"center\">\
    			<select name=\"dhcpOrStatic\">\
    		    	<option %s value=\"STATIC\">STATIC</option>\
    		        <option %s value=\"DHCP\">DHCP</option>\
    			</select>\
    		</td>\
        </tr>\
        <tr>\
            <th>IP Address (when using STATIC)</th>\
            <td><input type=\"text\" name=\"ipAddress\" value=\"%d.%d.%d.%d\"></td>\
        </tr>\
        <tr>\
            <th>Subnet Mask</th>\
            <td><input type=\"text\" name=\"subnetMask\" value=\"%d.%d.%d.%d\"></td>\
        </tr>\
        <tr>\
            <th>Gateway</th>\
            <td><input type=\"text\" name=\"gateway\" value=\"%d.%d.%d.%d\"></td>\
        </tr>\
        <tr>\
            <th>DNS 1</th>\
            <td><input type=\"text\" name=\"dns1\" value=\"%d.%d.%d.%d\"></td>\
        </tr>\
        <tr>\
            <th>DNS 2</th>\
            <td><input type=\"text\" name=\"dns2\" value=\"%d.%d.%d.%d\"></td>\
        </tr>\
    </table>\
    <div class=\"button-container\">\
        <button type=\"submit\" class=\"action-button\">Save Network Config</button>\
    	<h6>You should wait 10 second after hitting Save Network Config button and then type in new ip address in address bar.</h6>\
    </div>\
    </form>\
</body>\
</html>";

const char* webpage_css = "h1, .h1"                        \
					"{"                              \
					"font-family: Roboto;"           \
					"font-weight: bold;"             \
					"font-size: 27px;"               \
					"text-decoration: none;"         \
					"color: #000000;"                \
					"background-color: transparent;" \
					"margin: 0px 0px 0px 0px;"       \
					"padding: 0px 0px 0px 0px;"      \
					"display: inline;"               \
					"}"                              \
					"h2, .h2"                        \
					"{"                              \
					"font-family: Roboto;"           \
					"font-weight: bold;"             \
					"font-size: 27px;"               \
					"text-decoration: none;"         \
					"color: #000000;"                \
					"background-color: transparent;" \
					"margin: 0px 0px 0px 0px;"       \
					"padding: 0px 0px 0px 0px;"      \
					"display: inline;"               \
					"}"                              \
					"h3, .h3"                        \
					"{"                              \
					"font-family: Roboto;"           \
					"font-weight: bold;"             \
					"font-size: 27px;"               \
					"text-decoration: none;"         \
					"color: #000000;"                \
					"background-color: transparent;" \
					"margin: 0px 0px 0px 0px;"       \
					"padding: 0px 0px 0px 0px;"      \
					"display: inline;"               \
					"}"                              \
					"h4, .h4"                        \
					"{"                              \
					"font-family: Roboto;"           \
					"font-weight: bold;"             \
					"font-size: 27px;"               \
					"font-style: italic;"            \
					"text-decoration: none;"         \
					"color: #000000;"                \
					"background-color: transparent;" \
					"margin: 0px 0px 0px 0px;"       \
					"padding: 0px 0px 0px 0px;"      \
					"display: inline;"               \
					"}"                              \
					"h5, .h5"                        \
					"{"                              \
					"font-family: Roboto;"           \
					"font-weight: bold;"             \
					"font-size: 19px;"               \
					"text-decoration: none;"         \
					"color: #000000;"                \
					"background-color: transparent;" \
					"margin: 0px 0px 0px 0px;"       \
					"padding: 0px 0px 0px 0px;"      \
					"display: inline;"               \
					"}"                              \
					"h6, .h6"                        \
					"{"                              \
					"font-family: Roboto;"           \
					"font-weight: bold;"             \
					"font-size: 16px;"               \
					"text-decoration: none;"         \
					"color: #000000;"                \
					"background-color: transparent;" \
					"margin: 0px 0px 0px 0px;"       \
					"padding: 0px 0px 0px 0px;"      \
					"display: inline;"               \
					"}"                              \
					".CustomStyle"                   \
					"{"                              \
					"font-family: \"Roboto\";"       \
					"font-weight: bold;"             \
					"font-size: 16px;"               \
					"text-decoration: none;"         \
					"color: #2E74B5;"                \
					"background-color: transparent;" \
					"}";
const char* option_str = "<label for=\"\" id=\"Label1\" style=\"position:absolute;left:90px;top:75px;width:197px;height:27px;line-height:27px;z-index:41;\">PCB Firmware Version :</label>"\
					"<input type=\"text\" id=\"Editbox1\" style=\"position:absolute;left:330px;top:75px;width:152px;height:20px;z-index:42;\" name=\"Editbox1\" value=\"%s\" spellcheck=\"false\">"\
					"<label for=\"\" id=\"Label3\" style=\"position:absolute;left:90px;top:150px;width:197px;height:27px;line-height:27px;z-index:43;\">Active Temperature :</label>"\
					"<input type=\"text\" id=\"Editbox2\" style=\"position:absolute;left:330px;top:150px;width:152px;height:20px;z-index:44;\" name=\"Editbox2\" value=\"%s\" spellcheck=\"false\">"\
					"<label for=\"\" id=\"Label4\" style=\"position:absolute;left:90px;top:225px;width:197px;height:27px;line-height:27px;z-index:45;\">Active PIR State :</label>"\
					"<input type=\"text\" id=\"Editbox3\" style=\"position:absolute;left:330px;top:225px;width:152px;height:20px;z-index:46;\" name=\"Editbox3\" value=\"%s\" spellcheck=\"false\">"\
					"<label for=\"\" id=\"Label5\" style=\"position:absolute;left:90px;top:300px;width:197px;height:27px;line-height:27px;z-index:47;\">Last IR command seen :</label>"\
					"<input type=\"text\" id=\"Editbox4\" style=\"position:absolute;left:330px;top:300px;width:152px;height:20px;z-index:48;\" name=\"Editbox4\" value=\"%s\" spellcheck=\"false\">"\
					"</form>"\
					"</div>"\
					"<div id=\"wb_Form3\" style=\"position:absolute;left:760px;top:86px;width:700px;height:805px;z-index:49;\">"\
					"<form name=\"Form3\" method=\"get\" action=\"/IP\" enctype=\"multipart/form-data\" id=\"Form3\" onsubmit=\"submitFormInBackground()\" >"\
					"<div id=\"wb_Heading2\" style=\"position:absolute;left:250px;top:23px;width:243px;height:33px;z-index:0;\">"\
					"<h1 id=\"Heading2\">Configuration</h1></div>"\
					"</select>"\
					"<label for=\"\" id=\"Label7\" style=\"position:absolute;left:49px;top:68px;width:197px;height:27px;line-height:27px;z-index:2;\">PIR Alarm ON/OFF</label>"\
					"<select name=\"PIR\" size=\"1\" id=\"mySelect2\" onchange=\"sendLink2()\" style=\"position:absolute;left:387px;top:68px;width:114px;height:34px;z-index:2;\">"\
					"<option value=\"1\" %s>ON</option>"\
					"<option value=\"2\" %s>OFF</option>"\
					"</select>"\
					"<label for=\"\" id=\"Label6\" style=\"position:absolute;left:49px;top:106px;width:197px;height:27px;line-height:27px;z-index:3;\">TEMP Alarm ON/OFF</label>"\
					"<select name=\"TEMP\" size=\"1\" id=\"mySelect3\" onchange=\"sendLink3()\" style=\"position:absolute;left:387px;top:106px;width:114px;height:34px;z-index:6;\">"\
					"<option value=\"1\" %s>ON</option>"\
					"<option value=\"2\" %s>OFF</option>"\
					"</select>"\
					"<label for=\"\" id=\"Label8\" style=\"position:absolute;left:49px;top:144px;width:197px;height:27px;line-height:27px;z-index:5;\">TV Type</label>"\
					"<select name=\"TV\" size=\"1\" id=\"mySelect4\" onchange=\"sendLink4()\" style=\"position:absolute;left:387px;top:144px;width:114px;height:34px;z-index:4;\">"\
					"<option value=\"1\" %s>Samsung</option>"\
					"<option value=\"2\" %s>LG</option>"\
					"<option value=\"3\" %s>Panasonic</option>"\
					"<option value=\"4\" %s>Sony</option>"\
					"<option value=\"5\" %s>RC5</option>"\
					"<option value=\"6\" %s>RC6</option>"\
					"<option value=\"7\" %s>Sharp</option>"\
					"</select>"\
					"<label for=\"\" id=\"Label24\" style=\"position:absolute;left:49px;top:182px;width:197px;height:27px;line-height:27px;z-index:5;\">LOOPON</label>"\
					"<select name=\"LOOPON\" size=\"1\" id=\"mySelect5\" onchange=\"sendLink5()\" style=\"position:absolute;left:387px;top:180px;width:114px;height:34px;z-index:4;\">"\
					"<option value=\"1\" %s>ON</option>"\
					"<option value=\"2\" %s>OFF</option>"\
					"</select>"\
					"<label for=\"\" id=\"Label25\" style=\"position:absolute;left:49px;top:219px;width:197px;height:27px;line-height:27px;z-index:5;\">LOOPOFF</label>"\
					"<select name=\"LOOPOFF\" size=\"1\" id=\"mySelect6\" onchange=\"sendLink6()\" style=\"position:absolute;left:387px;top:217px;width:114px;height:34px;z-index:4;\">"\
					"<option value=\"1\" %s>ON</option>"\
					"<option value=\"2\" %s>OFF</option>"\
					"</select>"\
					"<label for=\"\" id=\"Label26\" style=\"position:absolute;left:49px;top:256px;width:197px;height:27px;line-height:27px;z-index:9;\">LOOP TIME</label>"
					"<input type=\"number\" id=\"Editbox16\" style=\"position:absolute;left:387px;top:254px;width:256px;height:25px;z-index:8;\" name=\"loop_time\" value=\"%s\" spellcheck=\"false\">"\
					"<label for=\"Combobox1\" id=\"Label9\" style=\"position:absolute;left:49px;top:293px;width:197px;height:27px;line-height:27px;z-index:7;\">Pir Delay ON</label>"\
					"<input type=\"number\" id=\"Editbox5\" style=\"position:absolute;left:387px;top:291px;width:256px;height:25px;z-index:8;\" name=\"pir_delay_on\" value=\"%s\" spellcheck=\"false\">"\
					"<label for=\"\" id=\"Label10\" style=\"position:absolute;left:49px;top:330px;width:197px;height:27px;line-height:27px;z-index:9;\">Pir Delay OFF</label>"\
					"<input type=\"number\" id=\"Editbox6\" style=\"position:absolute;left:387px;top:328px;width:256px;height:25px;z-index:10;\" name=\"pir_delay_off\" value=\"%s\" spellcheck=\"false\">"\
					"<label for=\"\" id=\"Label11\" style=\"position:absolute;left:49px;top:367px;width:233px;height:27px;line-height:27px;z-index:11;\">Temperature Min threshold</label>"\
					"<input type=\"number\" id=\"Editbox7\" style=\"position:absolute;left:387px;top:365px;width:256px;height:25px;z-index:12;\" name=\"T_min_threshold\" value=\"%s\" spellcheck=\"false\">"\
					"<label for=\"\" id=\"Label12\" style=\"position:absolute;left:49px;top:404px;width:233px;height:27px;line-height:27px;z-index:13;\">Temperature Max threshold</label>"\
					"<input type=\"number\" id=\"Editbox8\" style=\"position:absolute;left:387px;top:402px;width:256px;height:25px;z-index:14;\" name=\"T_max_threshold\" value=\"%s\" spellcheck=\"false\">"\
					"<label for=\"\" id=\"Label13\" style=\"position:absolute;left:49px;top:441px;width:197px;height:27px;line-height:27px;z-index:15;\">IR command ON</label>"\
					"<input type=\"text\" id=\"Editbox9\" style=\"position:absolute;left:387px;top:439px;width:256px;height:25px;z-index:16;\" name=\"IR_com_on\" value=\"%s\" spellcheck=\"false\">"\
					"<label for=\"\" id=\"Label14\" style=\"position:absolute;left:49px;top:478px;width:197px;height:27px;line-height:27px;z-index:17;\">IR command OFF</label>"\
					"<input type=\"text\" id=\"Editbox10\" style=\"position:absolute;left:387px;top:476px;width:256px;height:25px;z-index:18;\" name=\"IR_com_off\" value=\"%s\" spellcheck=\"false\">"\
					"<label for=\"\" id=\"Label15\" style=\"position:absolute;left:49px;top:515px;width:197px;height:27px;line-height:27px;z-index:19;\">RS232 command ON</label>"\
					"<input type=\"text\" id=\"Editbox11\" style=\"position:absolute;left:387px;top:513px;width:256px;height:25px;z-index:20;\" name=\"RS232_com_on\" value=\"%s\" spellcheck=\"false\">"\
					"<label for=\"\" id=\"Label16\" style=\"position:absolute;left:49px;top:552px;width:197px;height:27px;line-height:27px;z-index:21;\">RS232 command OFF</label>"\
					"<input type=\"text\" id=\"Editbox12\" style=\"position:absolute;left:387px;top:550px;width:256px;height:25px;z-index:22;\" name=\"RS232_com_off\" value=\"%s\" spellcheck=\"false\">"\
					"<label for=\"\" id=\"Label17\" style=\"position:absolute;left:49px;top:589px;width:197px;height:27px;line-height:27px;z-index:23;\">RS232 setting RS1</label>"\
					"<input type=\"text\" id=\"Editbox13\" style=\"position:absolute;left:387px;top:587px;width:256px;height:25px;z-index:24;\" name=\"RS232_set_rs1\" value=\"%s\" spellcheck=\"false\">"\
					"<label for=\"\" id=\"Label18\" style=\"position:absolute;left:49px;top:626px;width:197px;height:27px;line-height:27px;z-index:25;\">RS232 setting RS2</label>"\
					"<input type=\"text\" id=\"Editbox14\" style=\"position:absolute;left:387px;top:624px;width:256px;height:25px;z-index:26;\" name=\"RS232_set_rs2\" value=\"%s\" spellcheck=\"false\">"\
					"<label for=\"\" id=\"Label19\" style=\"position:absolute;left:49px;top:663px;width:197px;height:27px;line-height:27px;z-index:27;\">RS232 setting RS3</label>"\
					"<input type=\"text\" id=\"Editbox15\" style=\"position:absolute;left:387px;top:661px;width:256px;height:25px;z-index:28;\" name=\"RS232_set_rs3\" value=\"%s\" spellcheck=\"false\">"\
					"<label for=\"Combobox1\" id=\"Label20\" style=\"position:absolute;left:653px;top:372px;width:13px;height:22px;line-height:22px;z-index:29;\">°F</label>"\
					"<label for=\"Combobox1\" id=\"Label21\" style=\"position:absolute;left:653px;top:405px;width:13px;height:22px;line-height:22px;z-index:30;\">°F</label>"\
					"<label for=\"Combobox1\" id=\"Label22\" style=\"position:absolute;left:653px;top:297px;width:13px;height:22px;line-height:22px;z-index:31;\">0.01s</label>"\
					"<label for=\"Combobox1\" id=\"Label23\" style=\"position:absolute;left:653px;top:260px;width:13px;height:22px;line-height:22px;z-index:32;\">s</label>"\
					"<label for=\"Combobox1\" id=\"Label27\" style=\"position:absolute;left:653px;top:335px;width:13px;height:22px;line-height:22px;z-index:33;\">s</label>"\
					"<input type=\"button\" id=\"Button5\" onclick=\"window.location.href='/load?read';return false;\" name=\"R\" value=\"READ CONFIG\" style=\"position:absolute;left:100px;top:700px;width:179px;height:49px;z-index:31;\">"\
					"<input type=\"submit\" id=\"Button6\" name=\"S\" value=\"SAVE CONFIG\" style=\"position:absolute;left:375px;top:700px;width:179px;height:49px;z-index:32;\">"\
					"</form>"\
					"<input type=\"button\" id=\"Button7\" onclick=\"window.location.href='/networksettings.html';\" value=\"NETWORK SETTINGS\" style=\"position:absolute;left:100px;top:755px;width:179px;height:49px;z-index:32;\">"\
					"<input type=\"button\" id=\"Button8\" onclick=\"window.location.href='/timesyncpage';\" value=\"TIME SYNC\" style=\"position:absolute;left:375px;top:755px;width:179px;height:49px;z-index:32;\">"\
					"</div>"\
					"</div>"\
					"</body>"\
					"</html>";
