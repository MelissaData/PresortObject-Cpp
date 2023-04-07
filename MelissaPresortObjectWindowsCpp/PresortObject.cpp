#include "PresortObject.h"

PresortObject::PresortObject(string license, string dataPath)
{
	// Set license string and set path to datafiles (.dat, etc)
	mdPresortObj->SetLicenseString(license.c_str());
	dataFilePath = dataPath;
	mdPresortObj->SetPathToPresortDataFiles(dataFilePath.c_str());

	// If you see a different date than expected, check your license string and either download the new data files or use the Melissa Updater program to update your data files.  
	mdPresort::ProgramStatus pStatus = mdPresortObj->InitializeDataFiles();

	if (pStatus != mdPresort::ProgramStatus::ErrorNone)
	{
		cout << "Failed to Initialize Object." << endl;
		cout << pStatus << endl;
		return;
	}

	cout << "                DataBase Date: " + string(mdPresortObj->GetDatabaseDate()) << endl;
	cout << "              Expiration Date: " + string(mdPresortObj->GetLicenseStringExpirationDate()) << endl;

	/**
	 * This number should match with the file properties of the Melissa Object binary file.
	 * If TEST appears with the build number, there may be a license key issue.
	 */
	cout << "               Object Version: " + string(mdPresortObj->GetBuildNumber()) << endl;
}

// This will call the lookup function to process the input phone as well as generate the result codes
void PresortObject::ExecuteObjectAndResultCodes(DataContainer& data)
{
	/* PreSortSettings to the desired type of Presort
	* The sample defaults to First Class Mailing, if you'd like to use Standard, comment out the current line and uncomment the one containing the enumeration: STD_LTR_AUTO
	* STD_LTR_AUTO is for Standard Mail, Letter, Automation pieces
	* FCM_LTR_AUTO = First Class Mail, Letter, Automation pieces
	*/
	mdPresortObj->SetPreSortSettings((int)mdPresort::SortationCode::FCM_LTR_AUTO);
	//presortObj.PreSortSettings(PresortObjLib.SortationCode.STD_LTR_AUTO);

	/* Sack and Parcel Dimensions */
	mdPresortObj->SetSackWeight("30");
	mdPresortObj->SetPieceLength("9");
	mdPresortObj->SetPieceHeight("4.5");
	mdPresortObj->SetPieceThickness("0.042");
	mdPresortObj->SetPieceWeight("1.5");

	/* Mailers ID
	* Insert a valid 6-9 digit MailersID number
	* If you do not have a valid Mailers ID, you can visit the USPS to apply for one. Go to usps.com and click on the 'Business Customer Gateway' link at the bottom of the page.
	*/
	mdPresortObj->SetMailersID("123456");

	/* Postage Payment Methods
	* If both of these functions are set to false (Default setting), then Metered Mail will be used.
	* Permit Imprint - Mailing without affixing postage. When set to true, current mailing will use permit imprint as method of postage payment
	*/
	//presortObj.PSPermitImprint = false; // way the mailer pays for his mailing

	/*	Precanceled Stamp - Cancellation of adhesive postage, stamped envelopes, or stamped cards before mailing.
	*	When set to true, PSPrecanceledStampValue must be set to the postage value in cents
	*/
	//presortObj.PSPrecanceledStamp = true;
	//presortObj.PSPrecanceledStampValue(0.10);

	/* Sorting Options
	* PSNCOA - Uses NCOALink for move updates
	*/
	mdPresortObj->SetPSNCOA(true);

	/* Post Office of Mailing Information - This is the Post office from where it will be mailed from */
	mdPresortObj->SetPSPostOfficeOfMailingCity("RSM");
	mdPresortObj->SetPSPostOfficeOfMailingState("CA");
	mdPresortObj->SetPSPostOfficeOfMailingZIP("92688");

	/* Update the Parameters
	* Verify and validate that the following properties were set to correct ranges: SetPieceHeight, SetPieceLength, SetPieceThickness,and SetPieceWeight
	*/
	if (mdPresortObj->UpdateParameters() == false)
	{
		cout << "Parameter Error: " + string(mdPresortObj->GetParametersErrorString()) << endl;
		cout << "\nAborting the program...\n" << endl;

		exit(1);
	}

	/* Add Input Records to Presort Object
	* Parse through the input file and add each record to the Presort Object
	*/
	ifstream reader;
	map<string, string> addressDict;

	try
	{
		reader.open(data.PresortFile);

		if (!reader.is_open())
		{
			throw runtime_error("Error opening file...");
		}

		string line;
		getline(reader, line); // header row

		while (getline(reader,line))
		{
			// Pre-determined format for test file
			string split[10];

			stringstream ss(line);
			
			for (int i = 0; i < 10; i++)
			{
				getline(ss, split[i], ',');
			}

			mdPresortObj->SetRecordID(split[0].c_str());
			string addressInfo = split[1] + "," + split[2] + "," + split[3] + "," + split[4] + "," + split[5] + "," + split[6] + "," + split[7] + "," + split[8] + "," + split[9];
			addressDict.emplace(split[0].c_str(), addressInfo);
			mdPresortObj->SetZip(split[6].c_str());
			mdPresortObj->SetPlus4(split[7].c_str());
			mdPresortObj->SetDeliveryPointCode(split[8].c_str());
			mdPresortObj->SetCarrierRoute(split[9].c_str());

			// Add record
			if (!mdPresortObj->AddRecord())
			{
				cout << "Error Adding Record " << split[0] << ": " << mdPresortObj->GetParametersErrorString() << endl;
			}
		}
	}
	catch(exception const& ex)
	{
		cout << "\nError Reading File: " << ex.what() << std::endl;
		cout << "\nAborting the program...\n" << std::endl;

		exit(1);
	}
	
	if (reader.is_open())
	{
		reader.close();
	}

	/* Do Presort - Do and check if Presort was successful, otherwise return the error.*/
	if (mdPresortObj->DoPresort() == false)
	{
		cout << "Error During Presort: " + string(mdPresortObj->GetParametersErrorString()) << endl;
		cout << "\nAborting the program...\n" << endl;

		exit(1);
	}

	/* Write Results */
	try
	{
		ofstream sw(data.OutputFile);

		// Write the headers on the first line
		sw << "RecID,MAK,Address,Suite,City,State,Zip,Plus4,DeliveryPointCode,CarrierRoute,TrayNumber,SequenceNumber,Endorsement,BundleNumber" << endl;

		// Grab the first record and continue through the file
		bool writeback = mdPresortObj->GetFirstRecord();
		while (writeback)
		{
			sw << mdPresortObj->GetRecordID() << "," << addressDict[mdPresortObj->GetRecordID()] << ","
				<< mdPresortObj->GetTrayNumber() << "," << mdPresortObj->GetSequenceNumber() << "," << mdPresortObj->GetEndorsementLine() << "," << mdPresortObj->GetBundleNumber() << endl;
			writeback = mdPresortObj->GetNextRecord();
		}

		sw.flush();
		sw.close();
	}
	catch (exception const& ex)
	{
		cout << "\nError Writing File: " << ex.what() << endl;
	}
}
