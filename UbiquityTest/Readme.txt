// (C) Copyright 2011 by Autodesk, Inc. 
//
// Permission to use, copy, modify, and distribute this software in
// object code form for any purpose and without fee is hereby granted, 
// provided that the above copyright notice appears in all copies and 
// that both that copyright notice and the limited warranty and
// restricted rights notice below appear in all supporting 
// documentation.

// AUTODESK PROVIDES THIS PROGRAM "AS IS" AND WITH ALL FAULTS. 
// AUTODESK SPECIFICALLY DISCLAIMS ANY IMPLIED WARRANTY OF
// MERCHANTABILITY OR FITNESS FOR A PARTICULAR USE.  AUTODESK, INC. 
// DOES NOT WARRANT THAT THE OPERATION OF THE PROGRAM WILL BE
// UNINTERRUPTED OR ERROR FREE.

// Use, duplication, or disclosure by the U.S. Government is subject to 
// restrictions set forth in FAR 52.227-19 (Commercial Computer
// Software - Restricted Rights) and DFAR 252.227-7013(c)(1)(ii)
// (Rights in Technical Data and Computer Software), as applicable.

// Author: Adam Nagy, October 2011 - Autodesk Developer Technical Services

Description:
This sample shows the functionalities of the Ubiquity API - non-COM properties

AutoCAD commands:
The sample defines the following AutoCAD commands:
 - SHOWPROPERTIES : Lists all the properties of the selected object in a tree control
 - CREATEMYCIRCLE : Creates our custom entity circle which provides additional properties
 - TOGGLEEXTRALINEPROPERTIES : Toggles if the extra two properties for line entities are shown or not in the property palette

Usage:
When you load this ARX application into AutoCAD then it will automatically 
register 2 extra properties for line entities under 'My Category' in
the property palette (OPM - Object Property Manager):
 - My Double Property: this is a double value
 - My Color Property: this is a color value

The actual value of the properties are stored in the entity's XData, and so to
change the value of the property you can either use the Property Palette or 
programmatically change the XData value.

If the ObjectARX 2013 SDK is not at "C:\ObjectARX 2013" on your system then: 
 - Inside Visual Studio go to "View >> Other Windows >> Property Manager" 
 - In the "Property Manager" window double-click on "Arx2013" 
 - Adjust the paths inside "Common Properties >> VC++ Directories" "Include Directories" and "Library Directories" 




