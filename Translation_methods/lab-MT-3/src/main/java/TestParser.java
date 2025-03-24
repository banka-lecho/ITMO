import org.junit.Assert;
import org.junit.Test;

import java.io.*;
import java.text.ParseException;

import org.apache.commons.io.FileUtils;

public class TestParser {
    @Test
    public void test1() throws IOException {
        File firstFile = new File("src/right_tests_output/test1");
        File secondFile = new File("src/tests_output/test1");

        boolean areFilesEqual = FileUtils.contentEquals(firstFile, secondFile);
        Assert.assertTrue(areFilesEqual);
    }

    @Test
    public void test2() throws IOException {
        File firstFile = new File("src/right_tests_output/test2");
        File secondFile = new File("src/tests_output/test2");

        boolean areFilesEqual = FileUtils.contentEquals(firstFile, secondFile);
        Assert.assertTrue(areFilesEqual);
    }

    @Test
    public void test3() throws IOException {
        File firstFile = new File("src/right_tests_output/test3");
        File secondFile = new File("src/tests_output/test3");

        boolean areFilesEqual = FileUtils.contentEquals(firstFile, secondFile);
        Assert.assertTrue(areFilesEqual);
    }

    @Test
    public void test4() throws IOException {
        File firstFile = new File("src/right_tests_output/test4");
        File secondFile = new File("src/tests_output/test4");

        boolean areFilesEqual = FileUtils.contentEquals(firstFile, secondFile);
        Assert.assertTrue(areFilesEqual);
    }

    @Test
    public void test5() throws IOException {
        File firstFile = new File("src/right_tests_output/test5");
        File secondFile = new File("src/tests_output/test5");

        boolean areFilesEqual = FileUtils.contentEquals(firstFile, secondFile);
        Assert.assertTrue(areFilesEqual);
    }

    @Test
    public void test6() throws IOException {
        File firstFile = new File("src/right_tests_output/test6");
        File secondFile = new File("src/tests_output/test6");

        boolean areFilesEqual = FileUtils.contentEquals(firstFile, secondFile);
        Assert.assertTrue(areFilesEqual);
    }

    @Test
    public void test7() throws IOException {
        File firstFile = new File("src/right_tests_output/test7");
        File secondFile = new File("src/tests_output/test7");

        boolean areFilesEqual = FileUtils.contentEquals(firstFile, secondFile);
        Assert.assertTrue(areFilesEqual);
    }

//    @Test
//    public void test8() throws IOException {
//        File firstFile = new File("src/right_tests_output/test8");
//        File secondFile = new File("src/tests_output/test8");
//
//        boolean areFilesEqual = FileUtils.contentEquals(firstFile, secondFile);
//        Assert.assertTrue(areFilesEqual);
//    }
}

