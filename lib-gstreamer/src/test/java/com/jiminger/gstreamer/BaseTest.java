package com.jiminger.gstreamer;

import java.io.File;
import java.net.URI;

import com.jiminger.gstreamer.util.GstUtils;

public class BaseTest {
   static {
      GstUtils.testMode();
   }

   public final static URI STREAM = new File(
         BaseTest.class.getClassLoader().getResource("test-videos/Libertas-70sec.mp4").getFile()).toURI();

}
