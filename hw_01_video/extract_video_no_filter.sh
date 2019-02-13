#!/bin/sh

#  extract_video.sh
#  Created by Jerry-Wanglaws 'n' Mingjun Gao on 2/10/19.


######## extract footages into image sequences ########

    if [ -d "$1" ]
    then
        cd $1;

        # make a directory for the image sequences
        mkdir -p "../image_sequences"
        # make a directory for the first round output videos
        mkdir -p "../first_processed_videos"
        # make a directory for the second round output videos
        mkdir -p "../second_processed_videos"


        # get the selfie videos and make a side by side video
        ffmpeg -i selfie1.mp4 \
        -i selfie2.mp4 \
        -filter_complex "[0:v:0]pad=iw*2:ih[bg]; [bg][1:v:0]overlay=w" \
        selfie_concated.mp4

        # loop through the directory and transform each mp4 video into image sequence
        for i in *.mp4; do
            echo $i
            # the backtick ` symbol means to evaluate the code inside first
            name=`echo $i | cut -d'.' -f1`;

            # input the videos in the current directory and convert it into image sequences
            ffmpeg -i "$i" -vf fps=3 "../image_sequences/${name}-%09d.png"

        done

    fi


######## choose the frames from each video and trasform back to clips ########

    cd ../image_sequences

    NAME="an_optimal_poem"

    ffmpeg -start_number 000000224 -i "${NAME}-%09d.png" -vframes 200 -c:v libx264 -pix_fmt yuv420p "../first_processed_videos/${NAME}_01.mp4"
    ffmpeg -start_number 000000698 -i "${NAME}-%09d.png" -vframes 300 -c:v libx264 -pix_fmt yuv420p "../first_processed_videos/${NAME}_02.mp4"
    ffmpeg -start_number 000001026 -i "${NAME}-%09d.png" -vframes 200 -c:v libx264 -pix_fmt yuv420p "../first_processed_videos/${NAME}_03.mp4"
    ffmpeg -start_number 000001288 -i "${NAME}-%09d.png" -vframes 150 -c:v libx264 -pix_fmt yuv420p "../first_processed_videos/${NAME}_04.mp4"
    ffmpeg -start_number 000001888 -i "${NAME}-%09d.png" -vframes 100 -c:v libx264 -pix_fmt yuv420p "../first_processed_videos/${NAME}_05.mp4"

    NAME="dots_norman_mclaren"

    ffmpeg -start_number 000000020 -i "${NAME}-%09d.png" -vframes 100 -c:v libx264 -pix_fmt yuv420p "../first_processed_videos/${NAME}_01.mp4"
    ffmpeg -start_number 0000000150 -i "${NAME}-%09d.png" -vframes 90 -c:v libx264 -pix_fmt yuv420p "../first_processed_videos/${NAME}_01.mp4"

    NAME="KANDINSKY DRAWING 1926"

    ffmpeg -start_number 000000010 -i "${NAME}-%09d.png" -vframes 255 -c:v libx264 -pix_fmt yuv420p "../first_processed_videos/${NAME}_01.mp4"
    ffmpeg -start_number 000000269 -i "${NAME}-%09d.png" -vframes 100 -c:v libx264 -pix_fmt yuv420p "../first_processed_videos/${NAME}_02.mp4"

    NAME="Triadisches Ballett von Oskar Schlemmer - Bauhaus"

    ffmpeg -start_number 000000109 -i "${NAME}-%09d.png" -vframes 300 -c:v libx264 -pix_fmt yuv420p "../first_processed_videos/${NAME}_01.mp4"
    ffmpeg -start_number 000000436 -i "${NAME}-%09d.png" -vframes 300 -c:v libx264 -pix_fmt yuv420p "../first_processed_videos/${NAME}_02.mp4"
    ffmpeg -start_number 000000913 -i "${NAME}-%09d.png" -vframes 300 -c:v libx264 -pix_fmt yuv420p "../first_processed_videos/${NAME}_03.mp4"
    ffmpeg -start_number 000001570 -i "${NAME}-%09d.png" -vframes 200 -c:v libx264 -pix_fmt yuv420p "../first_processed_videos/${NAME}_04.mp4"
    ffmpeg -start_number 000001815 -i "${NAME}-%09d.png" -vframes 400 -c:v libx264 -pix_fmt yuv420p "../first_processed_videos/${NAME}_05.mp4"
    ffmpeg -start_number 000003369 -i "${NAME}-%09d.png" -vframes 200 -c:v libx264 -pix_fmt yuv420p "../first_processed_videos/${NAME}_06.mp4"
    ffmpeg -start_number 000003875 -i "${NAME}-%09d.png" -vframes 200 -c:v libx264 -pix_fmt yuv420p "../first_processed_videos/${NAME}_07.mp4"
    ffmpeg -start_number 000004558 -i "${NAME}-%09d.png" -vframes 300 -c:v libx264 -pix_fmt yuv420p "../first_processed_videos/${NAME}_08.mp4"

    NAME="NYC Ballet Presents NEW BEGINNINGS"

    ffmpeg -start_number 000000052 -i "${NAME}-%09d.png" -vframes 150 -c:v libx264 -pix_fmt yuv420p "../first_processed_videos/${NAME}_01.mp4"
    ffmpeg -start_number 000000300 -i "${NAME}-%09d.png" -vframes 150 -c:v libx264 -pix_fmt yuv420p "../first_processed_videos/${NAME}_02.mp4"

    NAME="Collision"

    ffmpeg -start_number 000000025 -i "${NAME}-%09d.png" -vframes 100 -c:v libx264 -pix_fmt yuv420p "../first_processed_videos/${NAME}_01.mp4"
    ffmpeg -start_number 000000150 -i "${NAME}-%09d.png" -vframes 90 -c:v libx264 -pix_fmt yuv420p "../first_processed_videos/${NAME}_02.mp4"

    NAME="selfie_concated"

    ffmpeg -i "${NAME}-%09d.png" -c:v libx264 -pix_fmt yuv420p "../first_processed_videos/${NAME}_01.mp4"


######## scale all the videos so that they are of the same size ########

    cd ../first_processed_videos;

    for i in *.mp4; do

        echo $i
        # the backtick ` symbol means to evaluate the code inside first
        name=`echo $i | cut -d'.' -f1`;

        # input the videos in the current directory and convert it into image sequences
        ffmpeg -i "$i" -vf scale=438:360 "../second_processed_videos/${name}_second_processed.mp4"

    done


######## concatenate all the videos together ########

    cd ../second_processed_videos;

    FILE_COUNT=$#
    INPUTS=""
    FILTER=""
    INDEX=0

    #print the working directory and assign to a
    #variable
    ABS_PATH=$(pwd)

    #make a tmp directory if it doesn't already exist
    mkdir -p "tmp"

    #loop through all the mp4 files in our directory
    #and convert them all to quicktime files
    for i in *.mp4;
    do
        echo $i
        # the backtick ` symbol means to evaluate the code inside first
        name=`echo $i | cut -d'.' -f1`;
        echo $name;

        #convert the existing file to an h264 codec
        ffmpeg -i "$i" "tmp/${name}.mov";
        #then add the name and path to a concatenation file
        echo "file '$ABS_PATH/tmp/$name.mov'" >> files_to_concat.txt;
        echo "added $name to files_to_concat.txt";

    done

    # randomize the lines in the txt file
    shuf files_to_concat.txt --output files_to_concat_shufed.txt;

    # Now concatenate all files into one large video file
    # ffmpeg -f concat -safe 0 -i files_to_concat_shufed.txt -c copy "../concat_output.mov"
    ffmpeg -safe 0 -f concat -segment_time_metadata 1 -i files_to_concat_shufed.txt -vf select=concatdec_select -af aselect=concatdec_select,aresample=async=1 "../concat_output.mov"

    #clean up our tmp directory by removing it
    rm -rf tmp;


######## add audio for each first round processed video ########

    cd ..;

    ffmpeg -i concat_output.mov -i "audios/gongxifacai.mp3" \
    -c:v copy -c:a aac -strict experimental \
    -map 0:v:0 -map 1:a:0 finalized.mov







