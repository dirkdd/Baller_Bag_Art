#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <utility>
#include <numeric>

#include "./library/myFFmpegConversion.hpp"
#include "./library/metadataFunction.hpp"
#include "./library/dnaGenerator.hpp"
#include "./library/utils.hpp"

using namespace std;

int main(int argc, char *argv[])
{
    if(argc>=2){
        srand(time(NULL));
        const int scale = 512;
        const string outputFormat = "gif";
        const bool randomized = false;
        const bool unique = true;
        const bool shuffleOutput = true;
        vector<int> collectionSize = {25,25,125,125,350,350,1025,1025,1025,1025};
        const vector<vector<string>> layerDir = 
        {
    //GOAT   
    {"BACKGROUND_RARE", "BULLDOG_Pants", "BULLDOG_Arms", "BULLDOG_Shoes", "BULLDOG_Shirt", "BULLDOG_Necklace", "BULLDOG_Move", "BULLDOG_Ball"},
    {"BACKGROUND_RARE", "SHAM_GOD_Pants", "SHAM_GOD_Arms", "SHAM_GOD_Shoes", "SHAM_GOD_Shirt", "SHAM_GOD_Necklace", "SHAM_GOD_Move", "SHAM_GOD_Ball"},
    //PLATINUM    
    {"BACKGROUND", "BETWEEN_BEHIND_THE_BACK_Pants", "BETWEEN_BEHIND_THE_BACK_Arms", "BETWEEN_BEHIND_THE_BACK_Shoes", "BETWEEN_BEHIND_THE_BACK_Shirt", "BETWEEN_BEHIND_THE_BACK_Necklace", "BETWEEN_BEHIND_THE_BACK_Move", "BETWEEN_BEHIND_THE_BACK_Ball"},
    {"BACKGROUND", "BETWEEN_CROSSOVER_Pants", "BETWEEN_CROSSOVER_Arms", "BETWEEN_CROSSOVER_Shoes", "BETWEEN_CROSSOVER_Shirt", "BETWEEN_CROSSOVER_Necklace", "BETWEEN_CROSSOVER_Move", "BETWEEN_CROSSOVER_Ball"},    
    //GOLD
    {"BACKGROUND", "HESITATION_Pants", "HESITATION_Arms", "HESITATION_Shoes", "HESITATION_Shirt", "HESITATION_Necklace", "HESITATION_Move", "HESITATION_Ball"},
    {"BACKGROUND", "IN_N_OUT_Pants", "IN_N_OUT_Arms", "IN_N_OUT_Shoes", "IN_N_OUT_Shirt", "IN_N_OUT_Necklace", "IN_N_OUT_Move", "IN_N_OUT_Ball"},
    //SILVER
    {"BACKGROUND", "SPIN_MOVE_Pants", "SPIN_MOVE_Arms", "SPIN_MOVE_Shoes", "SPIN_MOVE_Shirt", "SPIN_MOVE_Necklace", "SPIN_MOVE_Move", "SPIN_MOVE_Ball"},
    {"BACKGROUND", "CROSSOVER_Pants", "CROSSOVER_Arms", "CROSSOVER_Shoes", "CROSSOVER_Shirt", "CROSSOVER_Necklace", "CROSSOVER_Move", "CROSSOVER_Ball"},
    //BRONZE
    {"BACKGROUND", "BETWEEN_THE_LEGS_Pants", "BETWEEN_THE_LEGS_Arms", "BETWEEN_THE_LEGS_Shoes", "BETWEEN_THE_LEGS_Shirt", "BETWEEN_THE_LEGS_Necklace", "BETWEEN_THE_LEGS_Move", "BETWEEN_THE_LEGS_Ball"},
    {"BACKGROUND", "BEHIND_THE_BACK_Pants", "BEHIND_THE_BACK_Arms", "BEHIND_THE_BACK_Shoes", "BEHIND_THE_BACK_Shirt", "BEHIND_THE_BACK_Necklace", "BEHIND_THE_BACK_Move", "BEHIND_THE_BACK_Ball"}
   
        };
        
        const string name = "Baller Bag Handles Package";
        const string description = "5,000 of the most unique, animated basketball moves in the world.";
        const string baseUri = "https://ballerbag.io";
        const vector<pair<string,string>> extraMetadata = 
        {
        {"Creator", "Justin Ho"}    
        };
        
        //only if u select Solana Chain
        const string symbol = "BallerBag";
        const string family = "BallerBag";
        const string sellerFeeBasisPoints = "750";
        const string externalUrl = "ballerbag.io";
        const vector<string> address = {"3XoRfWGPCoovn7wnyuwy7iXG8fTnh1nLw91zFnvsL4vL"};
        const vector<string> share = {"100"};
        
        //only if u want to generate a preview_gif or combine video + audio
        const int firstMedia = 0;
        const int numbOfMediaToGen = 10;
        //only if u want to generate a preview_gif
        const int fps = 30;
        //only if u want to combine video + audio
        const string inputVideoForm = "mp4";
        const string inputAudioForm = "mp3";
        const string outputVideoForm = "mp4";
        
        
        //from here u can ignore all
        const string chain = argv[1];
        string utility = "NULL";
        vector<vector<vector<string>>> singleLayer((int)collectionSize.size());
        vector<vector<vector<string>>> metadataSingleLayerName((int)collectionSize.size());
        vector<vector<vector<int>>> rarityWeight((int)collectionSize.size());
        vector<string> dnaOfAllMedia;
        vector<int> randomIndex;
        
        convertCollectionSize(collectionSize); 
        randomIndex.resize(collectionSize[(int)collectionSize.size()-1]);
        dnaOfAllMedia.resize(collectionSize[(int)collectionSize.size()-1]);
        if(argc==2){
            if((int)collectionSize.size()>=1){
                deleteAllFilesOfFolder("./tmp");
                deleteAllFilesOfFolder("./output/media");
                deleteAllFilesOfFolder("./output/json");
                deleteAllFilesOfFolder("./output/video_with_audio");
                deleteFile("./output/preview_gif.gif");
                for(int i=1;i<(int)collectionSize.size();++i){
                    readLayersAndRaritys(layerDir[i-1], singleLayer[i-1], metadataSingleLayerName[i-1], rarityWeight[i-1]);
                    if(randomized)
                        genAndSaveDnaRandomly(layerDir[i-1], singleLayer[i-1], collectionSize, i, dnaOfAllMedia, unique);
                    else
                        genAndSaveDnaWithRarity(layerDir[i-1], singleLayer[i-1], rarityWeight[i-1], collectionSize, i, dnaOfAllMedia, unique);
                }
                createRarityFile("./output/rarity_list.txt", collectionSize[(int)collectionSize.size()-1]);
                deleteCharactersFromDnas(dnaOfAllMedia);
                for(int i=1;i<(int)collectionSize.size();++i){
                    if(chain=="SOL")
                        generateAllMediaSolanaMetadata(layerDir[i-1], singleLayer[i-1], name, description, symbol, family, sellerFeeBasisPoints, externalUrl, address, share, extraMetadata, collectionSize, i, dnaOfAllMedia, outputFormat);
                    else
                        generateAllMediaMetadata(layerDir[i-1], metadataSingleLayerName[i-1], name, description, baseUri, extraMetadata, collectionSize, i, dnaOfAllMedia, outputFormat);
                    generateAllMedia(layerDir[i-1], singleLayer[i-1], collectionSize, i, scale, dnaOfAllMedia, outputFormat, chain);
                }
                if(shuffleOutput){
                    createShuffleFile(collectionSize[(int)collectionSize.size()-1]);
                    readRandomIndex(randomIndex, chain);
                    shuffleCollection(randomIndex, name, baseUri, outputFormat, chain, collectionSize[(int)collectionSize.size()-1]);
                }
                generateMetadataJson(collectionSize[(int)collectionSize.size()-1], chain);
            }
            else
                cerr << "error: the collection is empty" << endl;
        }
        else{
            utility = argv[2];
            
            if(utility=="update_info"){
                deleteAllFilesOfFolder("./output/json");
                readDnaFromFile(dnaOfAllMedia);
                deleteCharactersFromDnas(dnaOfAllMedia);
                for(int i=1;i<(int)collectionSize.size();++i){
                readLayersAndRaritys(layerDir[i-1], singleLayer[i-1], metadataSingleLayerName[i-1], rarityWeight[i-1]);
                    if(chain=="SOL")
                        generateAllMediaSolanaMetadata(layerDir[i-1], singleLayer[i-1], name, description, symbol, family, sellerFeeBasisPoints, externalUrl, address, share, extraMetadata, collectionSize, i, dnaOfAllMedia, outputFormat);
                    else
                        generateAllMediaMetadata(layerDir[i-1], metadataSingleLayerName[i-1], name, description, baseUri, extraMetadata, collectionSize, i, dnaOfAllMedia, outputFormat);
                }
                if(shuffleOutput){
                    readRandomIndex(randomIndex, chain);
                    reversePrevShuffle(chain, collectionSize[(int)collectionSize.size()-1], randomIndex, outputFormat);
                    shuffleCollection(randomIndex, name, baseUri, outputFormat, chain, collectionSize[(int)collectionSize.size()-1]);
                }
                generateMetadataJson(collectionSize[(int)collectionSize.size()-1], chain);
            }
            else if(utility=="preview_gif")
                generatePreviewGif(firstMedia, numbOfMediaToGen, scale, fps);
            else if(utility=="combine_video_with_audio")
                mergeAllAudioWithVideo(firstMedia, inputVideoForm, inputAudioForm, outputVideoForm, numbOfMediaToGen);
            else
                cerr << "parameters invalid, check your input" << endl;
        }
    }
    else
        cerr << "number of parameters invalid, check your input" << endl;
 return 0;
}
