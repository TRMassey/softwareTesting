/* Licensed to the Apache Software Foundation (ASF) under one or more
  * contributor license agreements.  See the NOTICE file distributed with
  * this work for additional information regarding copyright ownership.
  * The ASF licenses this file to You under the Apache License, Version 2.0
  * (the "License"); you may not use this file except in compliance with
  * the License.  You may obtain a copy of the License at
  *
  *      http://www.apache.org/licenses/LICENSE-2.0
  *
  * Unless required by applicable law or agreed to in writing, software
  * distributed under the License is distributed on an "AS IS" BASIS,
  * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  * See the License for the specific language governing permissions and
  * limitations under the License.
  */

import junit.framework.TestCase;

/**
  * Performs Validation Test for url validations.
  *
  * @version $Revision: 1128446 $ $Date: 2011-05-27 13:29:27 -0700 (Fri, 27 May 2011) $
  */
public class UrlValidatorTest extends TestCase {

  private boolean printStatus = false;
  private boolean printIndex = false; // print index that indicates current scheme,host,port,path, query test were using.

  public UrlValidatorTest(String testName) {
    super(testName);
  }

  public void testManualTest()
  {
    UrlValidator urlVal = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);

    System.out.println("\nAllowing all schemes: \n");
    // scheme
    System.out.println("\nShould Validate:");
    System.out.println("http://www.google.com");
    System.out.println(urlVal.isValid("http://www.google.com"));
    System.out.println("www.google.com");
    System.out.println(urlVal.isValid("www.google.com"));
    System.out.println("h3tp://www.google.com");
    System.out.println(urlVal.isValid("h3tp://www.google.com"));
    System.out.println("\nShould Not Validate:");
    System.out.println("http:/www.google.com");
    System.out.println(urlVal.isValid("://www.google.com"));
    System.out.println("://www.google.com");
    System.out.println(urlVal.isValid("://www.google.com"));

    // authority
    System.out.println("\nShould Validate:");
    System.out.println("http://www.google.com");
    System.out.println(urlVal.isValid("http://www.google.com"));
    System.out.println("http://www.google.au");
    System.out.println(urlVal.isValid("http://www.google.au"));
    System.out.println("\nShould Not Validate:");
    System.out.println("http://www.google~.com");
    System.out.println(urlVal.isValid("http://www.google~.com"));
    System.out.println("http://www.google");
    System.out.println(urlVal.isValid("http://www.google"));
    System.out.println("http://broke.hostname.com");
    System.out.println(urlVal.isValid("http://broke.hostname.com"));
    System.out.println("http://1.2.3");
    System.out.println(urlVal.isValid("http://1.2.3"));
    System.out.println("http://<blank>");
    System.out.println(urlVal.isValid("http:// "));
    

    // port
    System.out.println("\nShould Validate:");
    System.out.println("http://www.google.com:80");
    System.out.println(urlVal.isValid("http://www.google.com:80"));
    System.out.println("http://www.google.com:300");
    System.out.println(urlVal.isValid("http://www.google.com:300"));
    System.out.println("http://www.google.com:3000");
    System.out.println(urlVal.isValid("http://www.google.com:3000"));
    System.out.println("http://www.google.com:30000");
    System.out.println(urlVal.isValid("http://www.google.com:30000"));
    System.out.println("\nShould Not Validate:");
    System.out.println("http://www.google.com:");
    System.out.println(urlVal.isValid("http://www.google.com:"));
    System.out.println("http://www.google.com:-80");
    System.out.println(urlVal.isValid("http://www.google.com:-80a"));
    System.out.println("http://www.google.com:80");
    System.out.println(urlVal.isValid("http://www.google.com:80a"));

    // path
    System.out.println("\nShould Validate: ");
    System.out.println("http://www.google.com/test1");
    System.out.println(urlVal.isValid("http://www.google.com/test1"));
    System.out.println("http://www.google.com/");
    System.out.println(urlVal.isValid("http://www.google.com/"));
    System.out.println("\nShould Not Validate: ");
    System.out.println("http://www.google.comtest1");
    System.out.println(urlVal.isValid("http://www.google.comtest1"));
    System.out.println("http://www.google.com//test1");
    System.out.println(urlVal.isValid("http://www.google.com//test1"));
    System.out.println("http://www.google.com/..");
    System.out.println(urlVal.isValid("http://www.google.com/.."));
    System.out.println("http://www.google.com/../");
    System.out.println(urlVal.isValid("http://www.google.com/../"));
    System.out.println("http://www.google.com       /");
    System.out.println(urlVal.isValid("http://www.google.com         /"));
    

    // option
    System.out.println("\nShould Validate: ");
    System.out.println("http://www.google.com/test1/test1");
    System.out.println(urlVal.isValid("http://www.google.com/test1/test1"));
    System.out.println("http://www.google.com/test1/");
    System.out.println(urlVal.isValid("http://www.google.com/test1/"));
    System.out.println("http://www.google.com/test1test1");
    System.out.println(urlVal.isValid("http://www.google.com/test1test1"));
    System.out.println("\nShould Not Validate: ");
    System.out.println("http://www.google.comtest1test1");
    System.out.println(urlVal.isValid("http://www.google.comtest1test1"));
    System.out.println("http://www.google.com/test1//test1");
    System.out.println(urlVal.isValid("http://www.google.com/test1//test1"));

    // queries
    System.out.println("\nShould Validate:");
    System.out.println("http://www.google.com?action=view");
    System.out.println(urlVal.isValid("http://www.google.com?action=view"));
    System.out.println("http://www.google.com?action=view&hi=hello");
    System.out.println(urlVal.isValid("http://www.google.com?action=view&hi=hello"));
    System.out.println("\nShould Not Validate: ");
    System.out.println("http://www.google.com?action");
    System.out.println(urlVal.isValid("http://www.google.com?action="));
    System.out.println("http://www.google.com=view");
    System.out.println(urlVal.isValid("http://www.google.comaction=view"));
    System.out.println("http://www.google.com??action=view");
    System.out.println(urlVal.isValid("http://www.google.com??action=view"));

    UrlValidator urlVal2 = new UrlValidator(null, null, UrlValidator.NO_FRAGMENTS);
    System.out.println("\nAllowing No Fragments: \n");
    // scheme
    System.out.println("\nShould Validate:");
    System.out.println("http://www.google.com");
    System.out.println(urlVal2.isValid("http://www.google.com"));
    System.out.println("www.google.com");
    System.out.println(urlVal2.isValid("www.google.com"));
    System.out.println("h3tp://www.google.com");
    System.out.println(urlVal2.isValid("h3tp://www.google.com"));
    System.out.println("\nShould Not Validate:");
    System.out.println("http:/www.google.com");
    System.out.println(urlVal2.isValid("://www.google.com"));
    System.out.println("://www.google.com");
    System.out.println(urlVal2.isValid("://www.google.com"));

    // authority
    System.out.println("\nShould Validate:");
    System.out.println("http://www.google.com");
    System.out.println(urlVal2.isValid("http://www.google.com"));
    System.out.println("http://www.google.au");
    System.out.println(urlVal2.isValid("http://www.google.au"));
    System.out.println("\nShould Not Validate:");
    System.out.println("http://www.google~.com");
    System.out.println(urlVal2.isValid("http://www.google~.com"));
    System.out.println("http://www.google");
    System.out.println(urlVal2.isValid("http://www.google"));
    System.out.println("http://broke.hostname.com");
    System.out.println(urlVal2.isValid("http://broke.hostname.com"));
    System.out.println("http://1.2.3");
    System.out.println(urlVal2.isValid("http://1.2.3"));
    System.out.println("http://<blank>");
    System.out.println(urlVal2.isValid("http:// "));

    // port
    System.out.println("\nShould Validate:");
    System.out.println("http://www.google.com:80");
    System.out.println(urlVal2.isValid("http://www.google.com:80"));
    System.out.println("http://www.google.com:300");
    System.out.println(urlVal2.isValid("http://www.google.com:300"));
    System.out.println("http://www.google.com:3000");
    System.out.println(urlVal2.isValid("http://www.google.com:3000"));
    System.out.println("http://www.google.com:30000");
    System.out.println(urlVal2.isValid("http://www.google.com:30000"));
    System.out.println("\nShould Not Validate:");
    System.out.println("http://www.google.com:");
    System.out.println(urlVal2.isValid("http://www.google.com:"));
    System.out.println("http://www.google.com:-80");
    System.out.println(urlVal2.isValid("http://www.google.com:-80a"));
    System.out.println("http://www.google.com:80");
    System.out.println(urlVal2.isValid("http://www.google.com:80a"));

    // path
    System.out.println("\nShould Validate: ");
    System.out.println("http://www.google.com/test1");
    System.out.println(urlVal2.isValid("http://www.google.com/test1"));
    System.out.println("http://www.google.com/");
    System.out.println(urlVal2.isValid("http://www.google.com/"));
    System.out.println("\nShould Not Validate: ");
    System.out.println("http://www.google.comtest1");
    System.out.println(urlVal2.isValid("http://www.google.comtest1"));
    System.out.println("http://www.google.com//test1");
    System.out.println(urlVal2.isValid("http://www.google.com//test1"));
    System.out.println("http://www.google.com/..");
    System.out.println(urlVal2.isValid("http://www.google.com/.."));
    System.out.println("http://www.google.com/../");
    System.out.println(urlVal2.isValid("http://www.google.com/../"));

    // option
    System.out.println("\nShould Validate: ");
    System.out.println("http://www.google.com/test1/test1");
    System.out.println(urlVal2.isValid("http://www.google.com/test1/test1"));
    System.out.println("http://www.google.com/test1/");
    System.out.println(urlVal2.isValid("http://www.google.com/test1/"));
    System.out.println("http://www.google.com/test1test1");
    System.out.println(urlVal2.isValid("http://www.google.com/test1test1"));
    System.out.println("\nShould Not Validate: ");
    System.out.println("http://www.google.comtest1test1");
    System.out.println(urlVal2.isValid("http://www.google.comtest1test1"));
    System.out.println("http://www.google.com/test1//test1");
    System.out.println(urlVal2.isValid("http://www.google.com/test1//test1"));

    // queries
    System.out.println("\nShould Validate:");
    System.out.println("http://www.google.com?action=view");
    System.out.println(urlVal2.isValid("http://www.google.com?action=view"));
    System.out.println("http://www.google.com?action=view&hi=hello");
    System.out.println(urlVal2.isValid("http://www.google.com?action=view&hi=hello"));
    System.out.println("\nShould Not Validate: ");
    System.out.println("http://www.google.com?action");
    System.out.println(urlVal2.isValid("http://www.google.com?action="));
    System.out.println("http://www.google.com=view");
    System.out.println(urlVal2.isValid("http://www.google.comaction=view"));
    System.out.println("http://www.google.com??action=view");
    System.out.println(urlVal2.isValid("http://www.google.com??action=view"));

    UrlValidator urlVal3 = new UrlValidator(UrlValidator.ALLOW_LOCAL_URLS);
    System.out.println("\nAllowing local urls: \n");
    // scheme
    System.out.println("\nShould Validate:");
    System.out.println("http://www.google.com");
    System.out.println(urlVal3.isValid("http://www.google.com"));
    System.out.println("www.google.com");
    System.out.println(urlVal3.isValid("www.google.com"));
    System.out.println("h3tp://www.google.com");
    System.out.println(urlVal3.isValid("h3tp://www.google.com"));
    System.out.println("\nShould Not Validate:");
    System.out.println("http:/www.google.com");
    System.out.println(urlVal3.isValid("://www.google.com"));
    System.out.println("://www.google.com");
    System.out.println(urlVal3.isValid("://www.google.com"));

    // authority
    System.out.println("\nShould Validate:");
    System.out.println("http://www.google.com");
    System.out.println(urlVal3.isValid("http://www.google.com"));
    System.out.println("http://www.google.au");
    System.out.println(urlVal3.isValid("http://www.google.au"));
    // special, SHOULD allow at allow local
    System.out.println("http://hostname");
    System.out.println(urlVal3.isValid("http://hostname"));
    System.out.println("\nShould Not Validate:");
    System.out.println("http://www.google~.com");
    System.out.println(urlVal3.isValid("http://www.google~.com"));
    System.out.println("http://www.google");
    System.out.println(urlVal3.isValid("http://www.google"));
    System.out.println("http://broke.hostname.com");
    System.out.println(urlVal3.isValid("http://broke.hostname.com"));
    System.out.println("http://1.2.3");
    System.out.println(urlVal3.isValid("http://1.2.3"));
    System.out.println("http://<blank>");
    System.out.println(urlVal3.isValid("http:// "));

    // port
    System.out.println("\nShould Validate:");
    System.out.println("http://www.google.com:80");
    System.out.println(urlVal3.isValid("http://www.google.com:80"));
    System.out.println("http://www.google.com:300");
    System.out.println(urlVal3.isValid("http://www.google.com:300"));
    System.out.println("http://www.google.com:3000");
    System.out.println(urlVal3.isValid("http://www.google.com:3000"));
    System.out.println("http://www.google.com:30000");
    System.out.println(urlVal3.isValid("http://www.google.com:30000"));
    System.out.println("\nShould Not Validate:");
    System.out.println("http://www.google.com:");
    System.out.println(urlVal3.isValid("http://www.google.com:"));
    System.out.println("http://www.google.com:-80");
    System.out.println(urlVal3.isValid("http://www.google.com:-80a"));
    System.out.println("http://www.google.com:80");
    System.out.println(urlVal3.isValid("http://www.google.com:80a"));

    // path
    System.out.println("\nShould Validate: ");
    System.out.println("http://www.google.com/test1");
    System.out.println(urlVal3.isValid("http://www.google.com/test1"));
    System.out.println("http://www.google.com/");
    System.out.println(urlVal3.isValid("http://www.google.com/"));
    System.out.println("\nShould Not Validate: ");
    System.out.println("http://www.google.comtest1");
    System.out.println(urlVal3.isValid("http://www.google.comtest1"));
    System.out.println("http://www.google.com//test1");
    System.out.println(urlVal3.isValid("http://www.google.com//test1"));
    System.out.println("http://www.google.com/..");
    System.out.println(urlVal3.isValid("http://www.google.com/.."));
    System.out.println("http://www.google.com/../");
    System.out.println(urlVal3.isValid("http://www.google.com/../"));

    // option
    System.out.println("\nShould Validate: ");
    System.out.println("http://www.google.com/test1/test1");
    System.out.println(urlVal3.isValid("http://www.google.com/test1/test1"));
    System.out.println("http://www.google.com/test1/");
    System.out.println(urlVal3.isValid("http://www.google.com/test1/"));
    System.out.println("http://www.google.com/test1test1");
    System.out.println(urlVal3.isValid("http://www.google.com/test1test1"));
    System.out.println("\nShould Not Validate: ");
    System.out.println("http://www.google.comtest1test1");
    System.out.println(urlVal3.isValid("http://www.google.comtest1test1"));
    System.out.println("http://www.google.com/test1//test1");
    System.out.println(urlVal3.isValid("http://www.google.com/test1//test1"));

    // queries
    System.out.println("\nShould Validate:");
    System.out.println("http://www.google.com?action=view");
    System.out.println(urlVal3.isValid("http://www.google.com?action=view"));
    System.out.println("http://www.google.com?action=view&hi=hello");
    System.out.println(urlVal3.isValid("http://www.google.com?action=view&hi=hello"));
    System.out.println("\nShould Not Validate: ");
    System.out.println("http://www.google.com?action");
    System.out.println(urlVal3.isValid("http://www.google.com?action="));
    System.out.println("http://www.google.com=view");
    System.out.println(urlVal3.isValid("http://www.google.comaction=view"));
    System.out.println("http://www.google.com??action=view");
    System.out.println(urlVal3.isValid("http://www.google.com??action=view"));

    UrlValidator urlVal4 = new UrlValidator(0);
    System.out.println("\nDefault: \n");
    // scheme
    System.out.println("\nShould Validate:");
    System.out.println("http://www.google.com");
    System.out.println(urlVal4.isValid("http://www.google.com"));
    System.out.println("www.google.com");
    System.out.println(urlVal4.isValid("www.google.com"));
    System.out.println("h3tp://www.google.com");
    System.out.println(urlVal4.isValid("h3tp://www.google.com"));
    System.out.println("\nShould Not Validate:");
    System.out.println("http:/www.google.com");
    System.out.println(urlVal4.isValid("://www.google.com"));
    System.out.println("://www.google.com");
    System.out.println(urlVal4.isValid("://www.google.com"));

    // authority
    System.out.println("\nShould Validate:");
    System.out.println("http://www.google.com");
    System.out.println(urlVal4.isValid("http://www.google.com"));
    System.out.println("http://www.google.au");
    System.out.println(urlVal4.isValid("http://www.google.au"));
    System.out.println("\nShould Not Validate:");
    System.out.println("http://www.google~.com");
    System.out.println(urlVal4.isValid("http://www.google~.com"));
    System.out.println("http://www.google");
    System.out.println(urlVal4.isValid("http://www.google"));
    System.out.println("http://broke.hostname.com");
    System.out.println(urlVal4.isValid("http://broke.hostname.com"));
    System.out.println("http://1.2.3");
    System.out.println(urlVal4.isValid("http://1.2.3"));
    System.out.println("http://<blank>");
    System.out.println(urlVal4.isValid("http:// "));
    // special, should NOT allow at default
    System.out.println("http://hostname");
    System.out.println(urlVal4.isValid("http://hostname"));

    // port
    System.out.println("\nShould Validate:");
    System.out.println("http://www.google.com:80");
    System.out.println(urlVal4.isValid("http://www.google.com:80"));
    System.out.println("http://www.google.com:300");
    System.out.println(urlVal4.isValid("http://www.google.com:300"));
    System.out.println("http://www.google.com:3000");
    System.out.println(urlVal4.isValid("http://www.google.com:3000"));
    System.out.println("http://www.google.com:30000");
    System.out.println(urlVal4.isValid("http://www.google.com:30000"));
    System.out.println("\nShould Not Validate:");
    System.out.println("http://www.google.com:");
    System.out.println(urlVal4.isValid("http://www.google.com:"));
    System.out.println("http://www.google.com:-80");
    System.out.println(urlVal4.isValid("http://www.google.com:-80a"));
    System.out.println("http://www.google.com:80");
    System.out.println(urlVal4.isValid("http://www.google.com:80a"));

    // path
    System.out.println("\nShould Validate: ");
    System.out.println("http://www.google.com/test1");
    System.out.println(urlVal4.isValid("http://www.google.com/test1"));
    System.out.println("http://www.google.com/");
    System.out.println(urlVal4.isValid("http://www.google.com/"));
    System.out.println("\nShould Not Validate: ");
    System.out.println("http://www.google.comtest1");
    System.out.println(urlVal4.isValid("http://www.google.comtest1"));
    System.out.println("http://www.google.com//test1");
    System.out.println(urlVal4.isValid("http://www.google.com//test1"));
    System.out.println("http://www.google.com/..");
    System.out.println(urlVal4.isValid("http://www.google.com/.."));
    System.out.println("http://www.google.com/../");
    System.out.println(urlVal4.isValid("http://www.google.com/../"));

    // option
    System.out.println("\nShould Validate: ");
    System.out.println("http://www.google.com/test1/test1");
    System.out.println(urlVal4.isValid("http://www.google.com/test1/test1"));
    System.out.println("http://www.google.com/test1/");
    System.out.println(urlVal4.isValid("http://www.google.com/test1/"));
    System.out.println("http://www.google.com/test1test1");
    System.out.println(urlVal4.isValid("http://www.google.com/test1test1"));
    System.out.println("\nShould Not Validate: ");
    System.out.println("http://www.google.comtest1test1");
    System.out.println(urlVal4.isValid("http://www.google.comtest1test1"));
    System.out.println("http://www.google.com/test1//test1");
    System.out.println(urlVal4.isValid("http://www.google.com/test1//test1"));

    // queries
    System.out.println("\nShould Validate:");
    System.out.println("http://www.google.com?action=view");
    System.out.println(urlVal4.isValid("http://www.google.com?action=view"));
    System.out.println("http://www.google.com?action=view&hi=hello");
    System.out.println(urlVal4.isValid("http://www.google.com?action=view&hi=hello"));
    System.out.println("\nShould Not Validate: ");
    System.out.println("http://www.google.com?action");
    System.out.println(urlVal4.isValid("http://www.google.com?action="));
    System.out.println("http://www.google.com=view");
    System.out.println(urlVal4.isValid("http://www.google.comaction=view"));
    System.out.println("http://www.google.com??action=view");
    System.out.println(urlVal4.isValid("http://www.google.com??action=view"));

  }

  // scheme partition
  public void testYourFirstPartition() {
    System.out.println("\nTesting Schemes:\n");

    String[] ourSchemes = {"http://", "h3tp://", "://", ":/", " "};
    UrlValidator schemeVal = new UrlValidator(ourSchemes, 0);
    for (int i = 0; i < ourSchemes.length; i++) {
      String curScheme = ourSchemes[i];
      System.out.println("\nTesting " + curScheme);
      boolean valid = schemeVal.isValidScheme(curScheme);
      if (valid == false && i == 0 || valid == false && i == 1 || valid == true && i == 2 || valid == true && i == 3 || valid == false && i == 4) {
        System.out.println("FAILED, invalid scheme\n");
      } else {
    	System.out.println("PASSED\n");
      }
    }
  }

  // authority partition
  public void testYourSecondPartition() {
    System.out.println("\nTesting Authority:\n");

    String[] ourAuthority = {"www.google.com", "www.google~.com", "www.google", " ", "broke.hostname.com"};
    UrlValidator authVal = new UrlValidator(ourAuthority, 0);
    for (int i = 0; i < ourAuthority.length; i++) {
      String curAuth = ourAuthority[i];
      System.out.println("\nTesting " + curAuth);
      boolean valid = authVal.isValidAuthority(curAuth);
      if (valid == false && i == 0 || valid == true && i == 1 || valid == true && i == 2 || valid == true && i == 3 || valid == true && i == 4) {
        System.out.println("FAILED, invalid authority\n");
      } else {
    	System.out.println("PASSED\n");
      }
    }
  }

  // port partition - Done with the isValidAuthority(String authority) function
  public void testYourThirdPartition() {
    System.out.println("\nTesting Port:\n");

    String[] ourPort = {"www.google.com:80", "www.google.com:", "www.google.com:-80", "www.google.com:80a"};
    UrlValidator portVal = new UrlValidator(ourPort, 0);
    for (int i = 0; i < ourPort.length; i++) {
      String curPort = ourPort[i];
      System.out.println("\nTesting " + curPort);
      boolean valid = portVal.isValidAuthority(curPort);
      if (valid == false && i == 0 || valid == true && i == 1 || valid == true && i == 2 || valid == true && i == 3) {
       System.out.println("FAILED, invalid port\n");
      } else {
    	System.out.println("PASSED\n");
      }
    }
  }

  // path Partition
  public void testYourFourthPartition(){
    System.out.println("\nTesting Path:\n");

    String[] ourPath = {"/test1", "//test1", "/", "test1", ".."};
    UrlValidator pathVal = new UrlValidator(ourPath, 0);
    for (int i = 0; i < ourPath.length; i++) {
      String curPath = ourPath[i];
      System.out.println("\nTesting " + curPath);
      boolean valid = pathVal.isValidPath(curPath);
      if (valid == false && i == 0 || valid == true && i == 1 || valid == false && i == 2 || valid == true && i == 3) {
        System.out.println("FAILED, invalid path\n");
      } else {
    	System.out.println("PASSED\n");
      }
    }
  }


  // query Partition
  public void testYourFifthPartition() {
    System.out.println("\nTesting Queries:\n");

    String[] ourQueries = {"?action=view", "?action=", "/", "??action=view"};
    UrlValidator pathQuery = new UrlValidator(ourQueries, 0);
    for (int i = 0; i < ourQueries.length; i++) {
      String curQuery = ourQueries[i];
      System.out.println("\nTesting " + curQuery);
      boolean valid = pathQuery.isValidQuery(curQuery);
      if(valid == false && i == 0 || valid == true && i == 1 || valid == false && i == 2 || valid == true && i == 3) {
        System.out.println("FAILED, invalid Query\n");
      } else {
    	System.out.println("PASSED\n");
      }
    }
  }


  public void testIsValid() {
    int bugCount = 0;
    int length = 10;    // change as needed for loop count
    int k = 0;

    // set up valid parts
    String[] badUrls = new String[length];
    String[] trueSchemes = {"http://", "", "h3tp://"};
    String[] trueAuthority = {"www.google.com", "google.com"};
    String[] truePort = {":80", ":9", ":100"};
    String[] truePath = {"/test1", "/"};
    String[] trueOptions = {"/test1", "/test1/test1", " "};
    String[] trueQueries = {"?action=view", " "};


    // randomize valid each round and loop through "length" times
    System.out.println("\nTesting Known Valid Part Inputs:\n");
    for(int i = 0; i < length; i++) {
      // randomize
      int schemeInt = (int) (Math.random() * 2);
      int authorityInt = (int) (Math.random() * 2);
      int portInt = (int) (Math.random() * 3);
      int pathInt = (int) (Math.random() * 2);
      int optionsInt = (int) (Math.random() * 3);
      int queriesInt = (int) (Math.random() *2);

      // make string of valid parts in valid order
      String url = trueSchemes[schemeInt] + trueAuthority[authorityInt] + truePort[portInt] + truePath[pathInt] + trueQueries[queriesInt];
      UrlValidator validator = new UrlValidator();

      // check if it was marked valid
      boolean valid = validator.isValid(url);

      // if not valid, increase bug count and store url
      if(valid == false) {
        bugCount++;
        badUrls[k] = url;
        k++;
      }
    }
    // print results
    System.out.println("\nNumber of Bugs: " + bugCount + "\n");
    System.out.println("\nBad URLs: \n");
    for (int j = 0; j < badUrls.length; j++) {
      if(badUrls[j] != null){
    	System.out.println(badUrls[j] + "\n");
      }
    } 
  }

  public void testisValidQueryUnitTest()
  {
	  UrlValidator val = new UrlValidator();
	  System.out.println("\nUnit Test of isValidQuery\n");
	  System.out.println("\nTesting query ?action=view");
	  System.out.println("Result: " + val.isValidQuery("?action=view"));
	  System.out.println("\nTesting query null");
	  System.out.println("Result: " + val.isValidQuery(""));
	  System.out.println("\nTesting query ?page=1&test=0");
	  System.out.println("Result: " + val.isValidQuery("?page=1&test=0"));
  }
  
  public void testisValidSchemeUnitTest()
  {
	  UrlValidator val = new UrlValidator();
	  System.out.println("\nUnit Test of isValidScheme\n");
	  System.out.println("\nTesting scheme http");
	  System.out.println("Result: " + val.isValidScheme("http"));
	  System.out.println("\nTesting scheme https");
	  System.out.println("Result: " + val.isValidScheme("https"));
	  System.out.println("\nTesting scheme aaa");
	  System.out.println("Result: " + val.isValidScheme("aaa"));
	  System.out.println("\nTesting scheme ftp");
	  System.out.println("Result: " + val.isValidScheme("ftp"));
	  
  }

  /**
  * Create set of tests by taking the testUrlXXX arrays and
  * running through all possible permutations of their combinations.
  *
  * @param testObjects Used to create a url.
  */

}
