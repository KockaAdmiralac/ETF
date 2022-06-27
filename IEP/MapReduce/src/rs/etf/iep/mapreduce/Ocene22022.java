package rs.etf.iep.mapreduce;

import java.io.File;

import org.apache.commons.io.FileUtils;
import org.apache.hadoop.conf.Configuration;
import org.apache.hadoop.fs.Path;
import org.apache.hadoop.io.LongWritable;
import org.apache.hadoop.io.Text;
import org.apache.hadoop.mapreduce.Job;
import org.apache.hadoop.mapreduce.Mapper;
import org.apache.hadoop.mapreduce.Reducer;
import org.apache.hadoop.mapreduce.lib.input.FileInputFormat;
import org.apache.hadoop.mapreduce.lib.input.TextInputFormat;
import org.apache.hadoop.mapreduce.lib.output.FileOutputFormat;
import org.apache.hadoop.mapreduce.lib.output.TextOutputFormat;

public class Ocene22022 {
	private static final int MIN_INVALID_GRADE = 3;

	public static class Map1 extends Mapper<LongWritable, Text, Text, Text> {
		private String R;

		@Override
		public void setup(Context context) {
			R = context.getConfiguration().get("R");
		}

		@Override
		public void map(LongWritable key, Text value, Context context) {
			try {
				String[] split = value.toString().split("\t");
				if (split.length <= 1) {
					// Студент нема ниједан испит.
					return;
				}
				for (String exam : split[1].split(";")) {
					String[] examSplit = exam.split(",");
					if (examSplit[1].equals(R)) {
						context.write(new Text(examSplit[0]), new Text(examSplit[2] + "\t1"));
					}
				}
			} catch (Exception e) {
				// Хватају се све грешке јер Hadoop понекад може да их не испише.
				e.printStackTrace();
			}
		}
	}

	public static class Reduce1 extends Reducer<Text, Text, Text, Text> {
		private int N;

		@Override
		public void setup(Context context) {
			N = context.getConfiguration().getInt("N", MIN_INVALID_GRADE);
		}

		@Override
		public void reduce(Text key, Iterable<Text> values, Context context) {
			try {
				int studentCount = 0;
				int grade = MIN_INVALID_GRADE;
				for (Text value : values) {
					String[] valueSplit = value.toString().split("\t");
					grade = Integer.parseInt(valueSplit[0]);
					if (grade == N) {
						return;
					}
					studentCount += Integer.parseInt(valueSplit[1]);
				}
				context.write(key, new Text(grade + "\t" + studentCount));
			} catch (Exception e) {
				// Хватају се све грешке јер Hadoop понекад може да их не испише.
				e.printStackTrace();
			}
		}
	}

	public static void job1(String[] args) throws Exception {
		Configuration conf = new Configuration();
		conf.set("R", args[2]);
		conf.setInt("N", Integer.parseInt(args[3]));

		Job job = Job.getInstance(conf, "ocene2-1");
		job.setJarByClass(Ocene22022.class);

		job.setInputFormatClass(TextInputFormat.class);
		job.setOutputFormatClass(TextOutputFormat.class);

		job.setOutputKeyClass(Text.class);
		job.setOutputValueClass(Text.class);

		job.setMapperClass(Map1.class);
		job.setReducerClass(Reduce1.class);
		job.setCombinerClass(Reduce1.class);

		FileInputFormat.setInputPaths(job, new Path(args[0]));
		FileOutputFormat.setOutputPath(job, new Path("ocene2-temp"));

		job.waitForCompletion(true);
	}

	public static class Map2 extends Mapper<LongWritable, Text, Text, Text> {
		private static final Text text = new Text("ocene2-text");

		@Override
		public void map(LongWritable key, Text value, Context context) {
			try {
				context.write(text, value);
			} catch (Exception e) {
				// Хватају се све грешке јер Hadoop понекад може да их не испише.
				e.printStackTrace();
			}
		}
	}

	public static class Reduce2 extends Reducer<Text, Text, Text, Text> {
		@Override
		public void reduce(Text key, Iterable<Text> values, Context context) {
			try {
				int maxStudentCount = 0;
				String subject = null;
				for (Text value : values) {
					String[] valueSplit = value.toString().split("\t");
					int studentCount = Integer.parseInt(valueSplit[2]);
					if (studentCount > maxStudentCount) {
						maxStudentCount = studentCount;
						subject = valueSplit[0];
					}
				}
				context.write(new Text(subject), new Text(String.valueOf(maxStudentCount)));
			} catch (Exception e) {
				// Хватају се све грешке јер Hadoop понекад може да их не испише.
				e.printStackTrace();
			}
		}
	}

	public static void job2(String[] args) throws Exception {
		Job job = Job.getInstance();
		job.setJobName("ocene2-2");
		job.setJarByClass(Ocene22022.class);

		job.setInputFormatClass(TextInputFormat.class);
		job.setOutputFormatClass(TextOutputFormat.class);

		job.setOutputKeyClass(Text.class);
		job.setOutputValueClass(Text.class);

		job.setMapperClass(Map2.class);
		job.setCombinerClass(Reduce2.class);

		FileInputFormat.setInputPaths(job, new Path("ocene2-temp"));
		FileOutputFormat.setOutputPath(job, new Path(args[1]));

		job.waitForCompletion(true);
	}

	public static void main(String[] args) throws Exception {
		FileUtils.deleteDirectory(new File(args[1]));
		FileUtils.deleteDirectory(new File("ocene2-temp"));
		job1(args);
		job2(args);
	}
}
