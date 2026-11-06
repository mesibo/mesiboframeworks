# mesibo iOS SDK (CocoaPods Migration Notice)

⚠️ **CRITICAL NOTICE: CocoaPods Support Discontinued** ⚠️

The **mesibo** has fully migrated to Swift Package Manager (SPM). We no longer distribute frameworks, release updates, or provide development support via CocoaPods. 

If you are following a third-party internet tutorial or guide that tells you to add `pod 'mesibo'` to your `Podfile`, please **ignore those steps**. Remaining on the CocoaPods version will result in installation errors or outdated, unsupported binaries.

---

## 🚀 How to Migrate to Swift Package Manager (SPM)

The official distribution channel for the mesibo iOS SDK is now natively supported through Xcode via Swift Package Manager. This approach dramatically simplifies dependency syncing and avoids local build system conflicts.

### Option A: Install via Xcode GUI (Recommended)

1. Open your project or workspace in Xcode.
2. Navigate to the top menu and choose **File** ➔ **Add Package Dependencies...**
3. In the search box in the top-right corner, enter the official repository URL:
   ```text
   https://github.com/mesibo/mesibo-ios-sdk
   ```
4. Pick your desired version rule (for example, **Up to Next Major Version**).
5. Choose the core mesibo products your application target requires:
   * **`mesibo`**: Core real-time messaging, conferencing, and calls API.
   * **`MesiboUI`**: Ready-to-use messaging UI.
   * **`MesiboCall`**: Voice and video call UI.

### Option B: Declare via `Package.swift` (For Swift Packages)

If you manage your project using a standalone `Package.swift` file, declare the dependency array and target products directly like this:

```swift
dependencies: [
    .package(url: "https://github.com/mesibo/mesibo-ios-sdk", from: "2.10.0")
],
targets: [
    .target(
        name: "YourAppTarget",
        dependencies: [
            .product(name: "mesibo", package: "mesibo-ios-sdk"),
            .product(name: "MesiboUI", package: "mesibo-ios-sdk"),
            .product(name: "MesiboCall", package: "mesibo-ios-sdk")
        ]
    )
]
```

---

## 🛠️ Step-by-Step Clean Up Checklist

To successfully transition your current workspace away from the broken CocoaPods state, execute these steps in your terminal:

1. **Remove from Podfile:** Open your `Podfile` and completely delete the line containing `pod 'mesibo-ios-sdk'`.
2. **De-integrate CocoaPods:** Run a clean install on your workspace directory:
   ```bash
   pod install
   ```
3. **Clear your Local Caches:** Completely remove Xcode's cached operational directory to ensure old framework architectures do not conflict with SPM components:
   ```bash
   rm -rf ~/Library/Developer/Xcode/DerivedData
   ```
4. **Follow SPM Steps:** Implement **Option A** or **Option B** above to natively re-link the package dependencies.

For complete SDK guides, parameters, and initialize scripts, check our official [Mesibo Documentation Hub](https://mesibo.com).

