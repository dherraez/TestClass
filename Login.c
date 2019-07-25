Login()
{
	
	char *sCity;

	web_reg_find("SaveCount=WelcomeCount",
		"Text=Web Tours",
		LAST);

	web_reg_save_param_ex(
		"ParamName=User_ID",
		"LB=name=\"userSession\" value=\"",
		"RB=\"/>",
		SEARCH_FILTERS,
		LAST);
	
	lr_start_transaction("Proyecto_Dia24_Launch_T01");
	
	lr_rendezvous("Launch_Rendezvous");

	web_url("index.htm", 
		"URL=http://127.0.0.1:1080/WebTours/index.htm", 
		"TargetFrame=", 
		"Resource=0", 
		"RecContentType=text/html", 
		"Referer=", 
		"Snapshot=t1.inf", 
		"Mode=HTML", 
		LAST);
	
	atoi(lr_eval_string("{WelcomeCount}"));
	                     
	if (atoi(lr_eval_string("{WelcomeCount}")) > 6) {
		lr_end_transaction("Proyecto_Dia24_Launch_T01", LR_PASS);
	}
	
	else {
		lr_end_transaction("Proyecto_Dia24_Launch_T01", LR_FAIL);
		lr_error_message ("The count is not correct");
		lr_exit(LR_EXIT_ITERATION_AND_CONTINUE, LR_FAIL);
		
		//LR_EXIT_ITERATION_AND_CONTINUE
	}
	
	//lr_end_transaction("Proyecto_Dia24_Launch_T01", LR_AUTO);

	web_set_sockets_option("SSL_VERSION", "2&3");

	/* ******************LOGIN****************** */

	web_reg_find("Text=Web Tours", 
		LAST);

	lr_think_time(12);

lr_start_transaction("Login_T02");

			web_submit_data("login.pl", 
		"Action=http://127.0.0.1:1080/cgi-bin/login.pl", 
		"Method=POST", 
		"TargetFrame=body", 
		"RecContentType=text/html", 
		"Referer=http://127.0.0.1:1080/cgi-bin/nav.pl?in=home", 
		"Snapshot=t2.inf", 
		"Mode=HTML", 
		ITEMDATA, 
		"Name=userSession", "Value={User_ID}", ENDITEM, 
		"Name=username", "Value={User}", ENDITEM, 
		"Name=password", "Value={Password}", ENDITEM, 
		"Name=JSFormSubmit", "Value=off", ENDITEM, 
		"Name=login.x", "Value=53", ENDITEM, 
		"Name=login.y", "Value=17", ENDITEM, 
		LAST);

	lr_end_transaction("Login_T02", LR_AUTO);


	/* ***********GO TO FLIGHTS************** */

	web_reg_find("Text=Web Tours", 
		LAST);

	lr_think_time(27);
	
	
	
//	<option value="Frankfurt">Frankfurt</option>
//<option value="London">London</option>
//<option value="Los Angeles">Los Angeles</option>
//<option value="Paris">Paris</option>
		web_reg_save_param_ex(
		"ParamName=Cities",
		"LB=ption value=\"",
		"RB=\">",
		"Ordinal=ALL",
		SEARCH_FILTERS,
		LAST);

		

	web_url("Search Flights Button", 
		"URL=http://127.0.0.1:1080/cgi-bin/welcome.pl?page=search", 
		"TargetFrame=body", 
		"Resource=0", 
		"RecContentType=text/html", 
		"Referer=http://127.0.0.1:1080/cgi-bin/nav.pl?page=menu&in=home", 
		"Snapshot=t3.inf", 
		"Mode=HTML", 
		LAST);

	web_url("FormDateUpdate.class", 
		"URL=http://127.0.0.1:1080/WebTours/classes/FormDateUpdate.class", 
		"TargetFrame=", 
		"Resource=1", 
		"Referer=", 
		"Snapshot=t6.inf", 
		LAST);

	/* ********** SELECT DEPT an */

	web_reg_find("Text=Flight Selections", 
		LAST);

	lr_think_time(11);
	
	sCity = lr_paramarr_random("Cities");
	lr_save_string(sCity,"lr_City");

	web_submit_data("reservations.pl", 
		"Action=http://127.0.0.1:1080/cgi-bin/reservations.pl", 
		"Method=POST", 
		"TargetFrame=", 
		"RecContentType=text/html", 
		"Referer=http://127.0.0.1:1080/cgi-bin/reservations.pl?page=welcome", 
		"Snapshot=t7.inf", 
		"Mode=HTML", 
		ITEMDATA, 
		"Name=advanceDiscount", "Value=0", ENDITEM, 
		"Name=depart", "Value={lr_City}", ENDITEM, 
		"Name=departDate", "Value=07/25/2019", ENDITEM, 
		"Name=arrive", "Value=Paris", ENDITEM, 
		"Name=returnDate", "Value=07/26/2019", ENDITEM, 
		"Name=numPassengers", "Value=1", ENDITEM, 
		"Name=seatPref", "Value=None", ENDITEM, 
		"Name=seatType", "Value=Coach", ENDITEM, 
		"Name=.cgifields", "Value=roundtrip", ENDITEM, 
		"Name=.cgifields", "Value=seatType", ENDITEM, 
		"Name=.cgifields", "Value=seatPref", ENDITEM, 
		"Name=findFlights.x", "Value=65", ENDITEM, 
		"Name=findFlights.y", "Value=5", ENDITEM, 
		LAST);

	web_reg_find("Text=Flight Reservation", 
		LAST);

	lr_think_time(4);

	web_submit_data("reservations.pl_2", 
		"Action=http://127.0.0.1:1080/cgi-bin/reservations.pl", 
		"Method=POST", 
		"TargetFrame=", 
		"RecContentType=text/html", 
		"Referer=http://127.0.0.1:1080/cgi-bin/reservations.pl", 
		"Snapshot=t8.inf", 
		"Mode=HTML", 
		ITEMDATA, 
		"Name=outboundFlight", "Value=042;331;07/25/2019", ENDITEM, 
		"Name=numPassengers", "Value=1", ENDITEM, 
		"Name=advanceDiscount", "Value=0", ENDITEM, 
		"Name=seatType", "Value=Coach", ENDITEM, 
		"Name=seatPref", "Value=None", ENDITEM, 
		"Name=reserveFlights.x", "Value=61", ENDITEM, 
		"Name=reserveFlights.y", "Value=5", ENDITEM, 
		LAST);

	web_reg_find("Text=Reservation Made!", 
		LAST);

	web_submit_data("reservations.pl_3", 
		"Action=http://127.0.0.1:1080/cgi-bin/reservations.pl", 
		"Method=POST", 
		"TargetFrame=", 
		"RecContentType=text/html", 
		"Referer=http://127.0.0.1:1080/cgi-bin/reservations.pl", 
		"Snapshot=t9.inf", 
		"Mode=HTML", 
		ITEMDATA, 
		"Name=firstName", "Value=Jojo", ENDITEM, 
		"Name=lastName", "Value=Bean", ENDITEM, 
		"Name=address1", "Value=", ENDITEM, 
		"Name=address2", "Value=", ENDITEM, 
		"Name=pass1", "Value=Jojo Bean", ENDITEM, 
		"Name=creditCard", "Value=", ENDITEM, 
		"Name=expDate", "Value=", ENDITEM, 
		"Name=oldCCOption", "Value=", ENDITEM, 
		"Name=numPassengers", "Value=1", ENDITEM, 
		"Name=seatType", "Value=Coach", ENDITEM, 
		"Name=seatPref", "Value=None", ENDITEM, 
		"Name=outboundFlight", "Value=042;331;07/25/2019", ENDITEM, 
		"Name=advanceDiscount", "Value=0", ENDITEM, 
		"Name=returnFlight", "Value=", ENDITEM, 
		"Name=JSFormSubmit", "Value=off", ENDITEM, 
		"Name=.cgifields", "Value=saveCC", ENDITEM, 
		"Name=buyFlights.x", "Value=37", ENDITEM, 
		"Name=buyFlights.y", "Value=12", ENDITEM, 
		LAST);

	web_reg_find("Text=Web Tours", 
		LAST);

	lr_think_time(7);

	web_url("SignOff Button", 
		"URL=http://127.0.0.1:1080/cgi-bin/welcome.pl?signOff=1", 
		"TargetFrame=body", 
		"Resource=0", 
		"RecContentType=text/html", 
		"Referer=http://127.0.0.1:1080/cgi-bin/nav.pl?page=menu&in=flights", 
		"Snapshot=t10.inf", 
		"Mode=HTML", 
		LAST);

	return 0;
}
